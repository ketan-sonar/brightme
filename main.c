#include <math.h>
#include <stdio.h>

#include <ApplicationServices/ApplicationServices.h>

extern int DisplayServicesGetBrightness(CGDirectDisplayID id,
                                        float *brightness);

extern int DisplayServicesSetBrightness(CGDirectDisplayID id,
                                        float brightness);

int get_brightness(CGDirectDisplayID display)
{
    float brightness;
    if (DisplayServicesGetBrightness(display, &brightness) != 0) {
        fprintf(stderr, "ERROR: could not get the display brightness!");
        exit(1);
    }
    return roundf(brightness * 100);
}

void set_brightness(CGDirectDisplayID display, float brightness)
{
    if (DisplayServicesSetBrightness(display, brightness) != 0) {
        fprintf(stderr, "ERROR: could not set the display brightness!");
        exit(1);
    }
}

void usage(FILE *f, const char *program_name)
{
    fprintf(f, "Usage: %s [brightness (0-100)]\n", program_name);
}

int main(int argc, char **argv)
{
    const char *program_name = argv[0];

    CGDirectDisplayID main_display_id = CGMainDisplayID();

    if (argc == 1) {
        printf("Brightness: %d%%\n", get_brightness(main_display_id));
    } else if (argc == 2) {
        char *param = argv[1];
        char *endptr;
        errno = 0;
        long val = strtol(param, &endptr, 10);
        if (
            endptr == param || *endptr != '\0' ||
            ((val == LONG_MIN || val == LONG_MAX) && errno == ERANGE) ||
            val < 0 || val > 100
        ) {
            // no digits or non numeric chars found or val out of range
            usage(stderr, program_name);
            return EXIT_FAILURE;
        } else {
            float brightness = val / 100.0;
            set_brightness(main_display_id, brightness);
            printf(
                "Brightness set to %d%%\n",
                get_brightness(main_display_id)
            );
        }
    } else {
        usage(stderr, program_name);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
