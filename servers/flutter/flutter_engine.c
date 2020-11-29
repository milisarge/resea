#include <flutter_embedder.h>

const char *__program_name(void);
void printf(const char *fmt, ...);
void backtrace(void);

// ANSI escape sequences (SGR).
#define SGR_ERR      "\e[1;91m"  // Bold red.
#define SGR_WARN     "\e[0;33m"  // Yellow.
#define SGR_WARN_DBG "\e[1;33m"  // Bold yellow.
#define SGR_INFO     "\e[0;96m"  // Cyan.
#define SGR_DEBUG    "\e[1;32m"  // Bold green.
#define SGR_RESET    "\e[0m"

#define TRACE(fmt, ...)                                                        \
    do {                                                                       \
        printf("[%s] " fmt "\n", __program_name(), ##__VA_ARGS__);             \
    } while (0)

#define DBG(fmt, ...)                                                          \
    do {                                                                       \
        printf(SGR_DEBUG "[%s] " fmt SGR_RESET "\n", __program_name(),         \
               ##__VA_ARGS__);                                                 \
    } while (0)

#define INFO(fmt, ...)                                                         \
    do {                                                                       \
        printf(SGR_INFO "[%s] " fmt SGR_RESET "\n", __program_name(),          \
               ##__VA_ARGS__);                                                 \
    } while (0)

#define WARN(fmt, ...)                                                         \
    do {                                                                       \
        printf(SGR_WARN "[%s] WARN: " fmt SGR_RESET "\n", __program_name(),    \
               ##__VA_ARGS__);                                                 \
    } while (0)

#define WARN_DBG(fmt, ...)                                                     \
    do {                                                                       \
        printf(SGR_WARN_DBG "[%s] WARN: " fmt SGR_RESET "\n", __program_name(),\
               ##__VA_ARGS__);                                                 \
    } while (0)

#define ASSERT(expr)                                                           \
    do {                                                                       \
        if (!(expr)) {                                                         \
            printf(SGR_ERR "[%s] %s:%d: ASSERTION FAILURE: %s" SGR_RESET "\n", \
                   __program_name(),                                           \
                   __FILE__,                                                   \
                   __LINE__,                                                   \
                   #expr);                                                     \
            backtrace();                                                       \
            __builtin_unreachable();                                           \
        }                                                                      \
    } while (0)

#define OOPS(fmt, ...)                                                         \
    do {                                                                       \
        printf(SGR_WARN "[%s] Oops: " fmt SGR_RESET "\n", __program_name(),    \
               ##__VA_ARGS__);                                                 \
        backtrace();                                                           \
    } while (0)

#define NYI()                                                                  \
    do {                                                                       \
        printf(SGR_ERR "[%s] %s(): not yet ymplemented: %s:%d\n",              \
               __program_name(), __func__, __FILE__, __LINE__);                \
        __builtin_unreachable();                                               \
    } while (0)

#define UNREACHABLE()                                                          \
    do {                                                                       \
        printf(SGR_ERR "Unreachable at %s:%d (%s)\n" SGR_RESET, __FILE__,      \
               __LINE__, __func__);                                            \
        backtrace();                                                           \
        __builtin_unreachable();                                               \
    } while (0)


void _init();

typedef void (*ctor_func_t)(void);
extern ctor_func_t __preinit_array[];
extern ctor_func_t __preinit_array_end[];
extern ctor_func_t __init_array[];
extern ctor_func_t __init_array_end[];

static void call_ctors(void) {
    for (ctor_func_t *f = __preinit_array; f != __preinit_array_end; f++) {
        (*f)();
    }

    for (ctor_func_t *f = __init_array; f != __init_array_end; f++) {
        (*f)();
    }
}

static bool surface_present_callback(void* user_data, const void *allocation,
                                     size_t row_bytes, size_t height) {
    NYI();
}

static void platform_message_callback(const FlutterPlatformMessage *message,
                                      void *user_data) {
    NYI();
}

static void vsync_callback(void *user_data, intptr_t baton) {
    NYI();
}

static bool runs_task_on_current_thread_callback(void *user_data) {
    NYI();
}

static void post_task_callback(FlutterTask task, uint64_t target_time_ns,
                               void *user_data) {
    NYI();
}

const int argc = 2;
const char *const argv[argc + 1] = {
    "",
    "",
    NULL,
};

static FlutterRendererConfig config = {
    .type = kSoftware,
    .software = {
        .struct_size = sizeof(FlutterSoftwareRendererConfig),
        .surface_present_callback = surface_present_callback,
    },
};

static FlutterTaskRunnerDescription task_runner = {
    .struct_size = sizeof(FlutterTaskRunnerDescription),
    .user_data = NULL,
    .runs_task_on_current_thread_callback = runs_task_on_current_thread_callback,
    .post_task_callback = post_task_callback,
};

static FlutterProjectArgs args = {
    .struct_size = sizeof(FlutterProjectArgs),
    .assets_path = "/assets/",
    .icu_data_path = "/icu_data/",
    .command_line_argc = argc,
    .command_line_argv = argv,
    .platform_message_callback = platform_message_callback,
    .vm_snapshot_data = NULL,
    .vm_snapshot_data_size = 0,
    .vm_snapshot_instructions = NULL,
    .vm_snapshot_instructions_size = 0,
    .isolate_snapshot_data = NULL,
    .isolate_snapshot_data_size = 0,
    .isolate_snapshot_instructions = NULL,
    .isolate_snapshot_instructions_size = 0,
    .root_isolate_create_callback = NULL,
    .update_semantics_node_callback = NULL,
    .update_semantics_custom_action_callback = NULL,
    .persistent_cache_path = NULL,
    .is_persistent_cache_read_only = false,
    .vsync_callback = vsync_callback,
    .custom_dart_entrypoint = NULL,
    .custom_task_runners = &(FlutterCustomTaskRunners) {
        .struct_size = sizeof(FlutterCustomTaskRunners),
        .render_task_runner = &task_runner,
        .platform_task_runner = &task_runner,
    },
    .shutdown_dart_vm_when_done = true,
    .compositor = NULL,
};

static void *user_data = NULL;
static FlutterEngine engine;

void init(void) {
    INFO("Running global constructors...");
    call_ctors();
    INFO("Running FlutterEngineRun...");
    FlutterEngineRun(1, &config, &args, user_data, &engine);
}
