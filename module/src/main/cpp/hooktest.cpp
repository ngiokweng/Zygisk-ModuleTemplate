//
// Created by user on 2024/4/21.
//
#include "hooktest.h"

// C++ 函数
FILE *my_fopen(const char *filename, const char *modes)
{
    // 执行 stack 清理（不可省略）
    BYTEHOOK_STACK_SCOPE();
    FILE * ret;
    // 在调用原函数之前，做点什么....
    LOGD("prev fopen: %s", filename);
    if(strstr(filename,"file.txt")){
        ret = nullptr;
    }else{
        // 调用原函数（也可以不调用）（一般在这里传入原参数，也可以根据需要改变参数）
        FILE* fp = BYTEHOOK_CALL_PREV(my_fopen, filename, modes);
        ret = fp;
    }


    // 在调用原函数之后，做点什么....
    LOGD("after fopen");

    // 返回原函数的返回值（当然，也可以返回其他的值）
    return ret;
}

void hooked_callback(bytehook_stub_t task_stub, int status_code, const char *caller_path_name,
                     const char *sym_name, void *new_func, void *prev_func, void *arg){
    LOGD("sym_name=%s, status_code=%d,  arg: %s", sym_name, status_code, reinterpret_cast<char*>(arg));
}

void my_hook()
{
    // 因為是純native, 因此要這樣初始化
    bytehook_init(BYTEHOOK_MODE_AUTOMATIC, true);

    char* callback_arg = new char[20];
    strcpy(callback_arg, "callback arg");

    bytehook_hook_single(
            "liblessontest.so",
            nullptr,
            "fopen",
            reinterpret_cast<void *>(my_fopen),
            hooked_callback,
            callback_arg);
}