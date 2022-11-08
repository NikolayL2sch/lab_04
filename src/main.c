#include "errors.h"
#include "constants.h"

int main(void)
{
    int rc = 0;
    int stack_type;

    system("clear");

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
    else
        rc = compare_stacks();
    
    if (rc)
    {
        print_error(rc);
        return rc;
    }

    return rc;
}