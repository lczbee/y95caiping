#ifndef __DMA_OTA_WRAPPER_H__
#define __DMA_OTA_WRAPPER_H__

#include <stddef.h>
#include <stdbool.h>

#define TWS_OTA
#define DMA_OTA_DATA_BUFFER_SIZE_FOR_BURNING_DEFAULT_SIZE   (4096)
#define DMA_OTA_FLASH_SECTOR_SIZE                           (4096)


//#define DMA_OTA_DEBUG
#ifdef DMA_OTA_DEBUG
#include "stdio.h"
#define DMA_OTA_LOG_E(fmt, ...)         printf("[DMA_OTA] "fmt, ##__VA_ARGS__)
#define DMA_OTA_LOG_D(fmt, ...)         printf("[DMA_OTA] "fmt, ##__VA_ARGS__)
#define DMA_OTA_LOG_I(fmt, ...)         printf("[DMA_OTA] "fmt, ##__VA_ARGS__)
#define DMA_OTA_DUMP8(str, buf, cnt)    //DUMP8(str, buf, cnt)
#define DMA_OTA_ASSERT(cond, str, ...)  //ASSERT(cond, str, ##__VA_ARGS__)
#else
#define DMA_OTA_LOG_E(fmt, ...)
#define DMA_OTA_LOG_D(fmt, ...)
#define DMA_OTA_LOG_I(fmt, ...)
#define DMA_OTA_DUMP8(str, buf, cnt)
#define DMA_OTA_ASSERT(cond, str, ...)
#endif


typedef enum {
    DMA_OTA_TWS_UNKNOWN = 0,
    DMA_OTA_TWS_MASTER,
    DMA_OTA_TWS_SLAVE,
} DMA_OTA_TWS_ROLE_TYPE;


typedef  unsigned char   uint8_t;
typedef  unsigned int    uint32_t;
typedef  int             int32_t;
typedef  unsigned short  uint16_t;
typedef  short           int16_t;

//typedef void (*transmit_data_cb)(uint16_t size, uint8_t *data);

typedef void (*dma_ota_timeout_cb)(void *data);

typedef struct {
    /**
    * @brief DMA OTA ms����֮����ûص�����
    *
    * @param[in] cb      �ص�����
    * @param[in] data    ���ûص�����ʱ�����ص������Ĳ���
    * @param[in] ms      ���ٺ������ô˺���
    *
    * @return ����˵��
    *        -true ����timer�ɹ�
    *        -false ����timerʧ��
    * @note ms����֮�����cb�ص�������������data
    */
    bool (*callback_by_timeout)(dma_ota_timeout_cb cb,
                                void *data, uint32_t ms);

    /**
    * @brief ��ȡDMA�豸�汾��
    *
    * @param[out] fw_rev_0      4λ�̼��汾�ŵ�һλ
    * @param[out] fw_rev_1      4λ�̼��汾�ŵڶ�λ
    * @param[out] fw_rev_2      4λ�̼��汾�ŵ���λ
    * @param[out] fw_rev_3      4λ�̼��汾�ŵ���λ
    *
    * @return ����˵��
    *        -false ��ȡ�汾��ʧ��
    *        -true ��ȡ�汾�ųɹ�
    * @note ʹ��С��APP��DMA��OTA����Ҫ���豸�汾�ű���4λ����ʽΪxx.xx.xx.xx \n
    * ÿλȡֵ��ΧΪ0-99,ͬһ��Ʒ��ֹ��ͬ�̼�ʹ����ͬ�汾��
    */
    bool (*get_firmeware_version)(uint8_t *fw_rev_0, uint8_t *fw_rev_1,
                                  uint8_t *fw_rev_2, uint8_t *fw_rev_3);

    /**
    * @brief DMAЭ��ջ�ڴ�����
    *
    * @param[in] size    �ڴ������С
    *
    * @return ����˵��
    *        -NULL ��ʾ�ڴ�����ʧ��
    *        -��NULL ��ʾ�ڴ�����ɹ�
    * @note ���ڴ���������DMAЭ��ջ���ڴ������ֵ������4KB \n
    * �ýӿ�Ӧ��֤DMA�豸���κ�ʹ��ģʽ�¾��������ڴ棬�̰߳�ȫ
    */
    void *(*dma_ota_heap_malloc)(uint32_t size);

    /**
    * @brief DMAЭ��ջ�ڴ��ͷ�
    *
    * @param[in] ptr    �ͷ��ڴ��ַ
    *
    * @note �ýӿ�Ӧ��֤DMA�豸���κ�ʹ��ģʽ�¾����ͷ��ڴ棬�̰߳�ȫ
    */
    void (*dma_ota_heap_free)(void *ptr);

    /**
    * @brief ��ȡDMA�豸���ֻ�Э�̵�MTU
    *
    * @param[out] mtu   DMA�豸������Ƶ��MTU
    *
    * @return ����˵��
    *        -false ��ȡDMA�豸���ֻ�Э�̵�MTUʧ��
    *        -true ��ȡDMA�豸���ֻ�Э�̵�MTU�ɹ�
    *
    * @note TWS���豸Master�豸���øýӿڻ�ȡ���ֻ�֮���MTU \n
    *           Slave�豸�����øýӿ�
    *
    */
    bool (*get_mobile_mtu)(uint32_t *mtu);

    /**
    * @brief ��ȡTWS�豸֮���MTU
    *
    * @param[out] mtu   DMA�豸������Ƶ��MTU
    *
    * @return ����˵��
    *        -false ��ȡTWS�豸֮���MTUʧ��
    *        -true ��ȡTWS�豸֮���MTU�ɹ�
    *
    * @note TWS�����豸������øýӿ�������ͬ�ķ���ֵ
    *           ��TWS�����豸��ֻ���������豸���Բ�ע��˻ص�����
    */
    bool (*get_peer_mtu)(uint32_t *mtu);

    /**
    * @brief ��ȡTWS�豸�Ľ�ɫ
    *
    * @return ����˵��
    *        -DMA_OTA_TWS_UNKNOWN δ֪����
    *        -DMA_OTA_TWS_MASTER   ����Master
    *        -DMA_OTA_TWS_SLAVE    �Ӷ�Slave
    *
    * @note OTA�����л���øýӿڣ����ȡ����UNKNOWN�Ľ�ɫ����
    *           ��TWS�����豸��ֻ���������豸���Բ�ע��˻ص�����
    */
    DMA_OTA_TWS_ROLE_TYPE(*get_tws_role)(void);

    /**
    * @brief ��ȡTWS���Ҷ���ֻ�����Ƿ�����
    *
    * @return ����˵��
    *        -false ���Ҷ�δ����
    *        -true ���Ҷ�������
    *
    * @note OTA�����л���øýӿ�
    *           ��TWS�����豸��ֻ���������豸���Բ�ע��˻ص�����
    */
    bool (*is_tws_link_connected)(void);

    /**
    * @brief �������ݸ��ֻ�
    *
    * @param[in] size    �������ݵĴ�С
    * @param[in] data    ���͵�����
    *
    * @note OTA SDK���ֻ�֮�䴫�����ݣ�ֻ������������ \n
    */
    void (*send_data_to_mobile)(uint16_t size, uint8_t *data);

    /**
    * @brief �������ݸ���һֻ����
    *
    * @param[in] size    �������ݵĴ�С
    * @param[in] data    ���͵�����
    *
    * @note OTA SDK������֮�䴫�����ݣ��������������
    *           ��TWS�����豸��ֻ���������豸���Բ�ע��˻ص�����
    */
    void (*send_data_to_tws_peer)(uint16_t size, uint8_t *data);

    /**
    * @brief �洢OTA��ص����ݵ�flash������ͬ��д��
    *
    * @param[in] size    д�����ݵĴ�С
    * @param[in] data    д�������
    *
    * @note OTA�����д洢OTA��ص�����
    *           �������ݴ�С��24Bytes����ҪԤ��8Bytes
    */
    void (*save_ota_info)(uint16_t size, const uint8_t *data);

    /**
    * @brief ��flash��ȡOTA SDK�洢������
    *
    * @param[in] size    Ҫ��ȡ���ݵĴ�С������д�����ݵĴ�С
    * @param[in] buffer  ������ݵ�buffer
    *
    * @note ��ȡOTA�����д洢��OTA�������
    */
    void (*read_ota_info)(uint16_t size, uint8_t *buffer);

    /**
    * @brief ��ȡ����Image���ݵĵ�buffer
    *
    * @param[out] buffer      buffer�ĵ�ַ
    * @param[in] buffer       ��Ҫ��buffer��С(�ᴫ����flash sector��С4096Bytes)
    *
    * @return ����˵��
    *        ʵ��buffer��С(��õ���flash sector��С)
    *
    * @note ���ڻ����յ���image���ݣ�buffer�������write_image_data_to_flash�ص�һ��д�뵽flash
    */
    uint32_t (*get_flash_data_buffer)(uint8_t **buffer, uint32_t size);

    /**
    * @brief д��OTA Image���ݵ�flash
    *
    * @param[in] size           д�����ݵĴ�С
    * @param[in] data           д�������
    * @param[in] image_offset   �Ӵ�image offset����ʼд��
    * @param[in] sync           �����Ƿ�ͬ��д��flash
    *
    * @note OTA Image����д�뵽flash
    *       get_flash_data_buffer ��buffer���˻�д��
    *       image_offset��һ�����ۼӵģ����ܻ�ӽ�С��image_offset����д������
    *       �˽ӿ��ڵĴ���ʵ�֣�д����ǰҪ�Ȳ���Flash
    *       ��get_flash_data_buffer��flash sector 4KB��С
    *           �˽ӿڵ�image_offset����4KB����
    *           ÿ��д���С����4KB
    */
    void (*write_image_data_to_flash)(uint16_t size, uint8_t *data, uint32_t image_offset, bool sync);

    /**
    * @brief ��flash�ڶ�ȡOTA Image����
    *
    * @param[in] size           Ҫ��ȡ���ݵĴ�С
    * @param[in] buffer         ������ݵ�buffer
    * @param[in] image_offset   �Ӵ�image offset����ʼ��ȡ
    *
    * @note ��flash�ڶ�ȡOTA Image����
    */
    void (*read_image_data_from_flash)(uint16_t size, uint8_t *buffer, uint32_t image_offset);

    /**
    * @brief ��flash�ڲ���OTA Image����
    *
    * @param[in] size           Ҫ�������ݵĴ�С
    * @param[in] image_offset   �Ӵ�image offset����ʼ����
    *
    * @note ��flash�ڲ���OTA Image����
    *           ������4KB����ģ�DMA_OTA_FLASH_SECTOR_SIZE �ı���
    *           size�� DMA_OTA_FLASH_SECTOR_SIZE �ı���(image�����һ���ֲ���)
    *           image_offset �� DMA_OTA_FLASH_SECTOR_SIZE �ı���
    */
    void (*erase_image_data_from_flash)(uint16_t size, uint32_t image_offset);

    /**
    * @brief ����OTAģʽ
    *
    * @note ��ʼOTA���ص��˺���
    */
    void (*enter_ota_state)(void);

    /**
    * @brief �˳�OTAģʽ
    *
    * @param[in] error      �Ƿ��쳣�˳�
    *           -true   �쳣�˳�
    *           -false  �����˳�
    *
    * @note OTA�쳣�˳����������������ص��˺���
    */
    void (*exit_ota_state)(bool error);

    /**
    * @brief ��ʼOTA֮��дFlash֮ǰset Image��С
    *
    * @param[in] total_image_size      Image�ܴ�С
    *
    * @note #DMA_OTA_OPER.enter_ota_state֮��
    *       #DMA_OTA_OPER.write_image_data_to_flash֮ǰ
    *       ����ô˺�����֪ͨ�豸�¹̼���С
    *       �豸���������������ƫ�Ƶ�
    */
    void (*set_new_image_size)(uint32_t total_image_size);

    /**
    * @brief OTA���ݴ������
    *
    * @param[in] total_image_size      Image�ܴ�С
    *
    * @return ����˵��
    *           -true Image�̼�û������
    *           -false Image�̼�������
    *
    * @note OTA���ݴ�����ɺ�ص��˺����������ڴ˺��������̼���У��
    *           SDK�ڲ��������image���ݶ�flash��crc32У�飬
    *           crc32У���ʱ����ϴ˺������ص�ʱ�䲻�ɳ���10s��
    *           OTAЭ�鷵�����ݰ���APP�ĳ�ʱʱ����10s������10s��OTAʧ�ܡ�
    */
    bool (*data_transmit_complete_and_check)(uint32_t total_image_size);

    /**
    * @brief OTA����check��ɺ�Ļص�
    *
    * @param[in] check_pass      �����̼�У��ɹ����
    *               - true �̼�У��û���⣨��ΪTWS���������߶�û���⣩
    *               - true �̼�У�������⣨��ΪTWS����������һ�������⣩
    *
    * @note OTA���ݴ��䲢У����ɺ�ص��˺���
    */
    void (*image_check_complete)(bool check_pass);

    /**
    * @brief Ӧ���µĹ̼���ϵͳ������ʹ���µĹ̼�����
    *
    * @return ����˵��
    *           -true   Ӧ���µĹ̼��ɹ�
    *           -false  Ӧ���µĹ̼�ʧ��
    *
    * @note Ӧ���µĹ̼���ϵͳ������ʹ���µĹ̼�������
    *       ֻ�й̼�У��ͨ�����Ż��ߵ�������á�
    *       �˽ӿ���Ҫ���أ�SDK��Ҫ�ڷ��غ�response��APP
    */
    bool (*image_apply)(void);

    // TODO: about role switch
} DMA_OTA_OPER;


#ifdef __cplusplus
extern "C" {
#endif


/**
* @brief ֹͣOTA�����ú�APP����ʾ����ʧ��
*
* @note ֹͣOTA�����������Ҫ���ô˽ӿ�
*       ��APP�����ӶϿ�������������
*       ����һ�߶����Ͽ������Ӷ���������
*       ׼�����������л��������л�ǰ����������
*       ������ҪֹͣOTA�������Ҳ���Ե��ô˽ӿڣ���Ҫ����������
*/
void dma_ota_stop_ota(void);

/**
* @brief �����ֻ����͵�����
*
* @param[in] size           ���ݵĴ�С
* @param[in] data           ����
* @param[in] isViaBle       �����Ƿ�ͨ��BLE����
* @param[in] isRelayToSlave �����Ƿ���Ҫ������ת�����Ӷ���
*
* @note
*      -# OTA SDK�����ֻ������ݣ����Ӷ�����ͨ���˽ӿ�ֱ���յ��ֻ��������� isRelayToSlave = false \n
*           ��isRelayToSlave����Ϊtrue��ʱ��SDK��ͨ�� #DMA_OTA_OPER.send_data_to_tws_peer �ص����� \n
*           ����OTA���ݸ���һֻ��������һֻ����ͨ�� #dma_ota_recv_tws_data ������������ \n
*      -# ��TWS�����豸��isRelayToSlave������false
*/
void dma_ota_recv_mobile_data(uint16_t size, uint8_t *data, bool isViaBle, bool isRelayToSlave);

/**
* @brief ������һֻ�������͵�����
*
* @param[in] size           ���ݵĴ�С
* @param[in] data           ����
*
* @note OTA SDK������һֻ�������͵�����
*       ��TWS�����豸�����ù��Ĵ˽ӿ�
*/
void dma_ota_recv_tws_data(uint16_t size, uint8_t *data);

/**
* @brief GET OTA��İ汾��
*
* @note ����ʱ���ô˽ӿڣ���ȡ�汾���ַ�������ʽ���� "1.0.1.0"
*/
const char *dma_ota_get_lib_version_string(void);

/**
* @brief ע��ص�����
*
* @param[in] operation      �������лص������Ľṹ�壬�ڲ�ֻ���ô˽ṹ���ָ��
*
* @note ��OTA SDK��ע�����еĻص��������ڲ�ֻ���ô˽ṹ���ָ�룬���ô˺�����ṹ���ڴ治Ҫ�ͷ�
*       �����ȵ��ô˽ӿ�ע�ắ��֮���ٵ��� #dma_ota_init ����
*/
void dma_ota_register_operation(DMA_OTA_OPER *operation);

/**
* @brief ��ʼ��OTA SDK
*
* @param[in] max_image_size ���image��С����λByte��ota�ļ����ɳ����˴�С
*
* @note ��ʼ��OTA SDK���ڿ�����ʱ�����
*         �����ڵ��ô˺���֮ǰ���� #dma_ota_register_operation ע��ص�������
*         �˺������߼�����ü����ص�����������ʼ��buffer�ͻ�ȡ�汾��
*/
void dma_ota_init(uint32_t max_image_size);


#ifdef __cplusplus
}
#endif

#endif // __DMA_OTA_WRAPPER_H__