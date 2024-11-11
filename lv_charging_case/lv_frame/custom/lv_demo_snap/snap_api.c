#include "snap_api.h"

// 发送拍照指令
void custom_client_send_snap()
{
    // 随便发个数就行，这里发1
    custom_client_send_ctrl_photo(1);
}
