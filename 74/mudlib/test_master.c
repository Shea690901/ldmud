/* Test Master.c
 *
 * Minimal master.c to provide a very rudimentary test of the gamedriver.
 * To perform the test, cd to the directory this file is in and give the
 * command
 *    driver -N -e -m. -Mtest_master.c -s-1 -sv-1 4242
 * (this assumes that you called the gamedriver 'driver' and that it is
 * in your searchpath).
 * Once it's running, telnet to localhost, port 4242. You should be
 * connected to the driver now and be able to enter commands.
 * The command 'help' will list you the commands available.
 *
 * A second test consists of the simple command
 *    driver --version
 * The driver shall just print the version and exit immediately.
 */

//---------------------------------------------------------------------------
void inaugurate_master (int arg)

// Initialise the master object.
// We have to set the uid hooks, else we can't clone a login object.

{
  set_driver_hook(2, unbound_lambda(({}), "uid"));
  set_driver_hook(3, unbound_lambda(({}), "uid"));
  set_driver_hook(10, "What?\n");
}

//---------------------------------------------------------------------------
void flag (string arg)

// Evaluate an argument given as option '-f' to the driver.

{
  if (arg == "shutdown")
  {
    shutdown();
    return;
  }
  write ("master: Unknown flag "+arg+"\n");
}

//---------------------------------------------------------------------------
mixed prepare_destruct (object obj)

// Prepare the destruction of the object.

{
  debug_message(sprintf("%O: prepare_destruct(%O)\n", this_object(), obj));
  return 0;
}

//---------------------------------------------------------------------------
object connect ()

// Handle the request for a new connection.
// We simply return a clone of ourself (we can't simply return this object
// unfortunately), the gamedriver will then call logon() here.

{
  object obj;
  debug_message(sprintf("%O: connect()\n", this_object()));
  obj = clone_object(file_name(this_object()));
  return obj;
}

//---------------------------------------------------------------------------
static nomask mixed logon ()

// A connection was successfully bound to this object.
// Print some status data and add the commands.

{
  debug_message(sprintf("%O: logon()\n", this_object()));
  write("\nAmylaar LPMud " __VERSION__ "\n\n----------\n");
  debug_info(4,0);
  write("----------\n\n> ");
  enable_commands();
  add_action("f_help", "help");
  add_action("f_shutdown", "shutdown");
  add_action("f_echo", "echo");
  add_action("f_flag", "flag");
  add_action("f_quit", "quit");

  return 1; // To verify that the connection was accepted.
}

//---------------------------------------------------------------------------
int f_help (string arg)

// The 'help' command.

{
  debug_message(sprintf("%O: f_help()\n", this_object()));
  write(
"  help     - Prints this message\n"
"  shutdown - shuts down the driver\n"
"  flag     - passes the argument to the flag() function\n"
"  echo     - tests the input_to() function\n"
"  quit     - terminates the connection, but leaves the driver running\n"
  );
  return 1;
}

//---------------------------------------------------------------------------
int f_flag (string arg)

// The 'flag' command.

{
  debug_message(sprintf("%O: f_flag()\n", this_object()));
  flag(arg);
  return 1;
}

//---------------------------------------------------------------------------
int f_echo (string arg)

// The 'echo' command.

{
  debug_message(sprintf("%O: f_echo()\n", this_object()));
  write("Please enter a line: ");
  input_to("echoline");
  return 1;
}

//---------------------------------------------------------------------------
void echoline (string text)

// The user entered some text. Echo it.

{
  debug_message(sprintf("%O: echoline()\n", this_object()));
  write("You entered: '"+text+"'\n");
}

//---------------------------------------------------------------------------
int f_shutdown (string arg)

// The 'shutdown' command.

{
  debug_message(sprintf("%O: f_shutdown()\n", this_object()));
  write("Shutting down.\n");
  shutdown();
  return 1;
}

//---------------------------------------------------------------------------
int f_quit (string arg)

// The 'quit' command.

{
  debug_message(sprintf("%O: f_quit()\n", this_object()));
  write("Bye-bye.\n");
  destruct(this_object());
  return 1;
}

