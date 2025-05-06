#include "../../include/state_machine/state_machine.h"

#include "../../include/logger/logger.h"
#include "../../include/pid/pid.h"
#include "../../include/state_machine/handlers/config_handler.h"
#include "../../include/state_machine/handlers/state_handler.h"
#include "../../include/state_machine/handlers/transition_handler.h"
#include "../../include/state_machine/state_machine_base.h"

void run_state_machine(void) {
    debug_print("Starting State Machine...");
    const StateMachine *sm = get_state_machine();

    while (sm->current_state != STATE_ERROR) {
        handle_state();

        if (sm->current_state != sm->next_state) {
            request_transition();
        }
    }
}
