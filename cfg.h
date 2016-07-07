#ifndef __CFG_H__
#define __CFG_H__

#define CFG_FILE_PATH "./station.cfg"

struct cdz_cfg_struct {
	char station_address[40];
	int  station_port;
};
int cdz_load_cfg(struct cdz_cfg_struct *ccs);

int cdz_sto_cfg(struct cdz_cfg_struct *ccs);

#endif
