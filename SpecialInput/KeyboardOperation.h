//
// Created by Isaac_Chen on 2020/2/29.
//

#ifndef SHELL_KEYBOARDOPERATION_H
#define SHELL_KEYBOARDOPERATION_H

#define CLEAR_OUTPUT_LINE() printf("\r\033[K")
#define MOVE_LEFT(y) printf("\033[%dD", (y))
#define MOVE_RIGHT(y) printf("\033[%dC",(y))
#define STORE_CURSOR() printf("\033[s")
#define RESTORE_CURSOR() printf("\033[u")

#endif //SHELL_KEYBOARDOPERATION_H
