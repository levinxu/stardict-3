#ifndef _STARDICT_DICT_MANAGE_H_
#define _STARDICT_DICT_MANAGE_H_

#include <list>
#include <string>
#include "lib/dictitemid.h"
#include "lib/utils.h"

enum DictManageItemType {
	LOCAL_DICT,
	VIRTUAL_DICT,
	NET_DICT,
};

struct DictManageItem {
	DictManageItemType type;
	bool enable;
	/* When type is LOCAL_DICT, file_or_id is path of the ifo file.
	When type is VIRTUAL_DICT or NET_DICT, file_or_id is path of the library file 
	implementing the respective plug-in. */
	DictItemId file_or_id;
};

struct DictManageGroup {
	std::string name;
	std::list<DictManageItem> querydict;
	std::list<DictManageItem> scandict;
};

struct DictManageInfo {
	std::list<DictManageGroup>::iterator get_active_group(void);
	std::list<DictManageGroup>::iterator set_active_group(const std::string& new_group);
	std::list<DictManageGroup> groups;
	std::string active_group;
};

class StarDictPlugins;
class show_progress_t;

extern void LoadDictInfo();
extern void GetUsedDictList(std::list<DictItemId> &dict_list);
extern void UpdateDictMask();
extern void UpdateDictList(std::list<DictItemId> &dict_new_install_list, show_progress_t *sp);
extern void UpdatePluginList(std::list<DictItemId> &plugin_new_install_list);
extern void UpdateConfigXML(
	const std::list<DictItemId> &dict_new_install_list,
	const std::list<DictItemId> &plugin_new_install_list,
	const StarDictPlugins* oStarDictPlugins);
extern void RemoveCacheFiles(void);

#endif
