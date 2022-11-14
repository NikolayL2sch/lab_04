#include "errors.h"
#include "constants.h"
#include "stack_arr_funcs.h"
#include "stack_list_funcs.h"
#include "stackio.h"
#include "measure_time.h"

int main(void)
{
    int rc = 0;
    int stack_type;

    rc = read_stack_type(&stack_type);

    if (rc)
    {
        print_error(rc);
        return rc;
    }

    if (stack_type == 1)
        rc = work_with_stack_array();
    else if (stack_type == 2)
        rc = work_with_stack_list();
    else if (stack_type == 3)
        rc = compare_stacks();
    
    if (rc)
    {
        print_error(rc);
        return rc;
    }

    return rc;
}
