//#include <utils_fix>
#include <utils_maths>
//#include <utils_vsync>
#include <utils_cmd>
#include <utils_colours>
#include <utils_vehicles>
#include <utils_player>
#include <utils_cuffs>

#include <YSI_Core\y_utils>

#include <logger>

#include <formatex>
FormatSpecifier<'m'>(output[], amount) {
    if (amount) {
        new
            i = 18,
            neg = amount < 0
        ;

        // The spaces must be there, otherwise strdel below won't work
        // on lower numbers.
        output = "$                ";

        // Null-out the end of it
        output[i] = 0;

        if (neg)
            amount = -amount;

        // Going right-left, add one number each time
        while (amount) {
            // Add a thousand separator every 3rd time
            if (!((i + 1) % 4))
                output[--i] = ',';

            // Now add the last digit of the number
            output[--i] = '0' + (amount % 10);

            // Then divide the number by 10, so digit in the end will be gone
            amount /= 10;
        }

        // Delete the spaces between the $-sign and the first (last) number
        strdel(output, 1, i);

        // Add a minus sign if needed
        if (neg)
            strins(output, "-", 1);
    } else {
        output = "$0";
    }
}