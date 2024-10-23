Copy over all the source files from `mt2/s2`. In the functions
concerned with starting ans stopping the thread, some of which
right now do just an early return if their call is not appropriate,
instead throw an exeption with a short text (either a string literal
in double quotes or an `std::string`)

First demonstrate that these exception arrive in the according
`catch` in main, but then add another `try - catch` in `parseAndExec`
so that these exceptions actually are caught locally and shown as
error message in the command line dialog without escaping to
`main`.