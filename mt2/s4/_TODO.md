Copy over all the source files from `mt2/s3`.

Define an empty class `ParseException` which is thrown when at the
end of all tests of valid commands no command matched. The little
menu of valid command should not be shown any longer before each
prompt but

(a) when the `ParseException` is caught (inside the loop so that
more commands can be entered)

(b) when it is requested with a new command (choose yoruself whether
you rather like to use `h` or `help` or `?` to issue that command.)