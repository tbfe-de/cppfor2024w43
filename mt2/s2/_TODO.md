Copy over all the source files from `mt2/s1` and set
enable execptions handling for the `std::ofstream xtty`
(which should have been copied over from the original
`main`) to `parseAndExec`.

For details see: https://en.cppreference.com/w/cpp/io/basic_ios/exceptions

