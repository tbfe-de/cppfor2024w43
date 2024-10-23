Copy over all the source files from `mt2/s4`.

Currently the command that ends the command input loop just uses
`break` as it did in `main` where it originally came from.
Instead now use `throw 0` and remove the "bye, bye" message.

(The intent is that when the loop ends the `catch` block for
`ìnt` in `main` displays something like:

"function main ended returning 0"
