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
    fprintf(f, "Usage: %s [brightness]\n", program_name);
}

int main(int argc, char **argv)
{
    const char *program_name = argv[0];

    CGDirectDisplayID main_display_id = CGMainDisplayID();

    if (argc == 1) {
        printf("Brightness: %d%%\n", get_brightness(main_display_id));
    } else if (argc == 2) {
        char *brightness_str = argv[1];
        float brightness = atoi(brightness_str) / 100.0;
        set_brightness(main_display_id, brightness);
        printf("Brightness set to %d%%\n", get_brightness(main_display_id));
    } else {
        usage(stderr, program_name);
        return 1;
    }

    return 0;
}
