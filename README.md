# bored-with-${\color{#FF0000}faults}$-and-${\color{#FF0000}leaks}$ 🧱

Efforts to develop secure constructs within the constraints of C's syntax.

## ${\color{#44A0FF} Hitherto} $

- (Failed) Attempt to make a stack based linked list for references stored in the list placed outside the function.
- (Failed) Attempt to make a function like macro to adhere to DRY. C's syntax restricts us to create reusable scopes. A function's basic function is to function like a container over repetitive code that might be used in any allowed scope i.e. program scope, file scope, other scopes or a function within a function. Attempt included trying to come up with a macro which defines another macro but this failed because of the restrictions within C's syntax. We can't have something like:

    ```C
    #define any_level_scope_creator(function_name, result_store, code) #define function_name(result_store) { code }
    ```

    Also, we can't afford to have a function instead of a scope for repetitive code as any references list manipulation will cause memory issues because the stack based linked list lies out of the function and anything created on the stack within a function will get destroyed after the function exits.
- (Experimenting) Investigate the development of macros capable of introducing local variables within defined scopes and functions, with the added functionality of maintaining a list of references to these variables within their respective scopes.

## ${\color{#FFAA00} Henceforth} $

- Target heap allocations instead of stack for references defined within a scope or a function as current implementation using stack memory causes inconsistency in the list and introduces various complexities.

## ${\color{#333333} Comments} $

I have been obsessing over this project. I tried to come close to a safe implementation in C for C programs and I think I need more time to figure out.

...C is fantastic for what it's designed for, and Rust is great in its own right. I'm a fan of both.
