-----------For configuring Visual Studio Express 2012-----------

.exe file requires msvcr100d.dll to run.

Go to PROJECT -> <project_name> properties... -> Configuration Properties ->
  Linker -> System -> SubSystem
  and select 'Windows(/SUBSYSTEM:WINDOWS)' for no background console.

Go to PROJECT -> <project_name> properties... -> Configuration Properties ->
  Linker -> Input -> Additional Dependencies
  and type 'allegro-5.0.10-monolith-md-debug.lib' for debug 
  Will solve the 'error LNK2001: unresolved external symbol <function_name>'.