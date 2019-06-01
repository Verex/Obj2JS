#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include "Transcriber.h"
#include "ModelParser.h"
using namespace std;
using namespace Obj2JS;

enum Options
{
    verbose = 1 << 0,
    flat = 1 << 1
};

/*
    TODO: Read format template from file for file output.
*/

int main(int argc, char *argv[])
{
    unsigned int options = 0;

    // Define argument start index.
    int argStart = 1;

    if (argc >= 3)
    {
        // Handle arguments while we can.
        while (argc > argStart && argv[argStart][0] == '-')
        {
            // Get argument lenght.
            int len = strlen(argv[argStart]);

            // Enforce option length.
            if (len >= 2)
            {
                // Check for long option
                if (argv[argStart][1] == '-')
                {
                    // TODO: HANDLE LONG OPTION.
                }
                else
                {
                    // Handle each option.
                    for (int i = 1; i < len; i++)
                    {
                        switch (argv[argStart][i])
                        {
                        case 'v':
                            // TODO: Handle voberse.
                            options += verbose;
                            break;
                        case 'f':
                            options += flat;
                            break;
                        case 't':
                            // Has to be solo parameter.
                            if (i > 1 || len > 2)
                            {
                                cout << "Unexpected option parameter 't'." << endl;
                                return 1;
                            }

                            if (++argStart >= argc)
                            {
                                cout << "Invalid argument count." << endl;
                                return 1;
                            }

                            cout << "T was: " << argv[argStart] << endl;

                            break;
                        default:
                            cout << "Invalid option parameter." << endl;
                            return 1;
                        }
                    }
                }
            }
            else
            {
                cout << "Option parameter empty." << endl;
                return 1;
            }

            // Increment argument start.
            argStart++;
        }

        // Ensure we still have args.
        if (argStart + 2 >= argc)
        {
            cout << "Invalid argument count." << endl;
            return 1;
        }

        // Get input and output files.
        string in = argv[argStart], out = argv[argStart + 1], meshName = argv[argStart + 2];

        // Set up model parser.
        ModelParser parser;

        // Load the model in the parser.
        if (!parser.LoadModel(in))
        {
            cout << "Obj model could not be loaded." << endl;
            return 1;
        }

        // Set up transcriber.
        Transcriber transcriber(meshName);

        // Write to the file.
        transcriber.WriteFile(out, parser.GetData((bool)(options & flat)));

        if (options & verbose)
        {
            cout << "Model converted to JS successfully." << endl;
        }

        return 0;
    }

    cout << "Invalid argument count." << endl;

    return 1;
}