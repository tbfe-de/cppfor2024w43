Improve the program structure by moving all the user interface
in a function `parseAndExec` in a separate file `parseAndExec.cpp`.
Provide a header file `parseAndExec.h` to be included in main.cpp`.

In the `main` function the call to `parseAndExec` should go into
a try block followed by these five `catch` blocks:

```
    catch (int errnum) {
        …
    }
    catch (char const *str){
        …
    }
    catch (std::string const& msg) {
        …
    }
    catch (std::except const &ex) {
        …
    }
    return EXIT_FAILURE;
```

The error handling in all cases should be to show the error
number, string, or message (in the last case the ẁhat` message.

For test purpose you may call `throw` from the `try` block.
