Add a feature to stop the greeter after some time in
one the following ways:

Quick and dirty:
Use a global variable `keep_greeter_running` and check
in th the `greeter` itself. Return the condition (you
hopefully have identified in the last step - otherwise
look how `MyClass` does it - which causes it not to be
scheduled for a next run.

To set that variable add a "one shot" (= non-repeating)
callback which sets that variable to false. As this is
a very short function you may consider to add it as a
lambda for being called by the TickerService after 25
seconds.

With more effort and more clean:
Add a second reference argument to the greeter accessing
the (global) `keep_greeter_running` to the `greeter`
function and make it "fit" to be registered as a client
of the `TickerService` using `std::bind` (or also a lambda)

Alternatively you may turn the `greeter` in a full-blown
class that way avoiding to make the `keep_greeter_running`
variable globally visible.
