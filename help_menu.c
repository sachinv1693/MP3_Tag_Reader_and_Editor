#include "main.h"

void help_menu(void)
{
		printf("\n------------------------------------------------------------------------\n");
		printf("Help menu for MP3 Tag Reader and Editor:\n\n");
		printf("For viewing the tags-   ./mp3_tag_reader -v <.mp3 file>\n\n");
		printf("For editing the tags-   ./mp3_tag_reader -e <.mp3 file> <modifier> <tag>\n\n");
		printf("Modifier\tFunction\n");
		printf("   -t   \tModifies Title tag\n");
		printf("   -T   \tModifies Track tag\n");
		printf("   -a   \tModifies Artist tag\n");
		printf("   -A   \tModifies Album tag\n");
		printf("   -y   \tModifies Year tag\n");
		printf("   -C   \tModifies Comment tag\n");
		printf("   -g   \tModifies Genre tag\n");
		printf("------------------------------------------------------------------------\n\n");
}

