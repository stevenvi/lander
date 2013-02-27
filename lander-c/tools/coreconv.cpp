/* coreconv
 *
 * opens the core files (.cor) from the original
 * LANDER! game and stores them into an ini file.
 *
 * This has the benefit of being much more user
 * friendly and easy to make hand modifications.
 *
 * Currently, all levels for the default game are
 * stored in core.ini, while expansion levels will
 * have their information stored in core_exp.ini.
 *
 */





#include <allegro.h>
#include <stdio.h>


int coreData[15];


void read_core(int num) {
	char fn[15];
	FILE *f;

	sprintf(fn,"%d.cor",num+1);
	if(!exists(fn))
	{
		allegro_message("%s NOT FOUND!\nPlease reinstall the game.\n\n"
			"If the problem persists,\ncontact your local software vendor.",strupr(fn));
		allegro_exit();
		exit(-1);
	}
	f = fopen(fn,"rb");
	fread(coreData,sizeof(int),15,f);
	fclose(f);


	// Put the core data in easier to understand places
/*	zoom2x = coreData[0];
	zoom2y = coreData[1];
	zoom5x = coreData[2];
	zoom5y = coreData[3];
	zoom10x= coreData[4];
	zoom10y= coreData[5];

	pad2x1 = coreData[6];
	pad2y  = coreData[7];
	pad2x2 = coreData[8];

	pad5x1 = coreData[9];
	pad5y  = coreData[10];
	pad5x2 = coreData[11];

	pad10x1= coreData[12];
	pad10y = coreData[13];
	pad10x2= coreData[14];
*/
}

int save_data(int num) {
	char section[256];
	sprintf(section,"level%02d",num);

	set_config_int(section,"zoom2x",coreData[0]);
	set_config_int(section,"zoom2y",coreData[1]);
	set_config_int(section,"zoom5x",coreData[2]);
	set_config_int(section,"zoom5y",coreData[3]);
	set_config_int(section,"zoom10x",coreData[4]);
	set_config_int(section,"zoom10y",coreData[5]);

	set_config_int(section,"pad2x1",coreData[6]);
	set_config_int(section,"pad2x2",coreData[8]);
	set_config_int(section,"pad2y",coreData[7]);

	set_config_int(section,"pad5x1",coreData[9]);
	set_config_int(section,"pad5x2",coreData[11]);
	set_config_int(section,"pad5y",coreData[10]);

	set_config_int(section,"pad10x1",coreData[12]);
	set_config_int(section,"pad10x2",coreData[14]);
	set_config_int(section,"pad10y",coreData[13]);
	
	return 0;
}


int main(int argc, char *argv[]) {
	allegro_init();
	set_config_file("core.ini");

	int i;
	for(i=0; i<9; i++) {
		read_core(i);
		save_data(i);
	}

	flush_config_file();
	return 0;
}
END_OF_MAIN();

