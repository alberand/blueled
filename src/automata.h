#ifndef __AUTOMATA_H__
#define __AUTOMATA_H__

/** Internal variables */
struct int_vars_t;

/** Current state */
static int current = 0;

/** Array with state functions */
#define AUTOMATA_INIT(N) do { \
        static int (*states[N])(struct int_vars_t * vars); \
    } while(0)

#define INITIAL(S) do{ current = S; } while(0)

#define AUTOMATA_STEP(V) do{ current = states[current](&V); } while(0)

#define STATE_INIT(S) do{ states[S] = _##S; } while(0)

#endif // __AUTOMATA_H__
