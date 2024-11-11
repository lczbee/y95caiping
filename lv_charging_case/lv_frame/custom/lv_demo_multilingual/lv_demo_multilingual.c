#include "lv_demo_multilingual.h"
#include "cpu.h"
#include "lvgl.h"
#include "usr_pic_index.h"

#if MULT_ENLAUGE_REMAP_ENABLE

//  初始化默认语言
#define DEFAULT_LANGUAGE    M_CHINESE_SIMPLIFIED

//  文字重映射表
const char * multilingualMap[][MULT_MAX] = {
{	[M_CHINESE_SIMPLIFIED] = "闹钟",  	[M_CHINESE_TRANSDITION] = 	"鬧鐘",  [M_ENGLISH] = 	"alarm clock",  [M_JAPANESE] = 	"目覚まし時計",  [M_KOREAN] = 	"알람 시계",  [M_FRENCH] = 	"Réveil",  [M_GERMEN] = 	"Wecker",  [M_RUSSIAN] = 	"Будильник",  [M_SPANISH] = 	"Despertador",  [M_PORTUGUESE] = 	"despertador",  [M_GREEK] = 	"ξυπνητήρι",  [M_DUTCH] = 	"wekker",  [M_POLISH] = 	"budzik",  [M_DANISH] = 	"vækkeur",  [M_ARABIC] = 	"منبه"},
{	"降噪模式",  		"降噪",  	"Noise reduction",  	"ノイズリダクション",  	"소음 감소",  	"Réduction du bruit",  	"Lärmreduzierung",  	"Снижение шума",  	"Reducción de ruido",  	"redução do ruído",  	"Μείωση θορύβου",  	"geluidsreductie",  	"redukcja hałasu",  	"støjreduktion",  	"الحد من الضوضاء"},
{	"屏幕亮度",  		"荧幕亮度",  	"Screen brightness",  	"スクリーンの輝度",  	"화면 밝기",  	"Luminosité de l'écran",  	"Bildschirmhelligkeit",  	"Яркость экрана",  	"Brillo de la pantalla",  	"Brilho do ecrã",  	"Φωτεινότητα οθόνης",  	"Schermverlichting",  	"Jasność ekranu",  	"Skærmlysstyrke",  	"سطوع الشاشة"},
{	"来电",  		"來電",  	"Incoming call",  	"着信",  	"전보",  	"Appel entrant",  	"Eingehender Anruf",  	"Входящий звонок",  	"Llamada",  	"Chamada recebida",  	"Εισερχόμενη κλήση",  	"Inkomende oproep",  	"Połączenie przychodzące",  	"Indgående opkald",  	"مكالمة واردة"},
{	"均衡器",  		"等化器",  	"Equalizer",  	"イコライザ",  	"이퀄라이저",  	"Égaliseur",  	"Equalizer",  	"Равновесие",  	"Igualador",  	"equalizador",  	"ισοσταθμιστής",  	"equalizer",  	"korektor",  	"equalizer",  	"التعادل"},
{	"标准",  		"標準",  	"Stand",  	"標準",  	"스탠",  	"Stand",  	"Stand",  	"Стд",  	"Est",  	"Pad",  	"Στντ",  	"Stand",  	"Stand",  	"Stand",  	"ستاندرد"},
{	"摇滚",  		"搖滾",  	"Rock",  	"ロック",  	"록",  	"Rock",  	"Rock",  	"Рок",  	"Rock",  	"Rock",  	"Ροκ",  	"Rock",  	"Rock",  	"Rock",  	"معي"},
{	"流行",  		"流行",  	"Pop",  	"ポプ",  	"팝",  	"Pop",  	"Pop",  	"Поп",  	"Pop",  	"Pop",  	"Ποπ",  	"Pop",  	"Pop",  	"Pop",  	"بوب"},
{	"经典",  		"經典",  	"Clas",  	"クラ",  	"클",  	"Clas",  	"Klas",  	"Клас",  	"Clás",  	"Clás",  	"Κλα",  	"Klas",  	"Klas",  	"Klas",  	"كلا"},
{	"爵士",  		"爵士",  	"Jazz",  	"ジャズ",  	"재즈",  	"Jazz",  	"Jazz",  	"Джаз.",  	"Jazz",  	"Jazz",  	"Τζαζ",  	"Jazz",  	"Jazz",  	"Jazz",  	"جاز ."},
{	"找到我的耳机",  		"找到我的耳機",  	"Find my headphones",  	"私のイヤホンを見つけて",  	"내 헤드폰 찾아봐",  	"Trouver mon casque",  	"Finden Sie meine Kopfhörer",  	"Найди мои наушники.",  	"Encuentra mis auriculares",  	"Encontra os meus auscultadores.",  	"Βρες τα ακουστικά μου.",  	"Zoek mijn koptelefoon",  	"Znajdź moje słuchawki.",  	"Find mine hovedtelefoner",  	"العثور على بلدي سماعة"},
{	"摘下耳机",  		"摘下耳機",  	"Take off headphones",  	"イヤホンを外す",  	"이어폰을 벗다",  	"Retirer les écouteurs",  	"Kopfhörer entfernen",  	"Снимите наушники.",  	"Quita los auriculares",  	"Remover os auscultadores",  	"Αφαίρεση ακουστικών",  	"Koptelefoon verwijderen",  	"Usuń słuchawki",  	"Fjern hovedtelefoner",  	"إزالة سماعة"},
{	"语言切换",  		"語言切換",  	"Language switching",  	"言語切り替え",  	"언어 전환",  	"Changement de langue",  	"Sprachwechsel",  	"Переключение языка",  	"Cambio de lenguaje",  	"Mudança de idioma",  	"Αλλαγή γλώσσας",  	"Taalwisseling",  	"Przełączanie języka",  	"Sprogskift",  	"لغة التبديل"},
{	"灯光",  		"燈光",  	"Lighting",  	"ライトらいと",  	"조명",  	"Lumières",  	"Beleuchtung",  	"Свет",  	"Luces",  	"iluminação",  	"φωτισμός",  	"verlichting",  	"oświetlenie",  	"belysning",  	"الإضاءة"},
{	"手机音乐",  		"手機音樂",  	"Mobile Music",  	"携帯音楽",  	"핸드폰 음악",  	"Musique pour téléphone portable",  	"Mobile Musik",  	"Мобильная музыка",  	"Música móvil",  	"Música Móvel",  	"Κινητή μουσική",  	"Mobiele muziek",  	"Muzyka mobilna",  	"Mobilmusik",  	"الهاتف المحمول الموسيقى"},
{	"SD音乐",  		"SD音樂",  	"SD Music",  	"SDミュージック",  	"SD 음악",  	"SD musique",  	"SD-Musik",  	"Музыка SD",  	"Música SD",  	"Música SD",  	"Μουσική SD",  	"SD-muziek",  	"Muzyka SD",  	"SD- musik",  	"SD الموسيقى"},
{	"即将切换到SD音乐，是否确定断开手机蓝牙？",  		"即將切換到SD音樂，是否確定斷開手機藍牙？",  	"About to switch to SD music. Are you sure you want to disconnect the phone's Bluetooth?",  	"SD音楽に切り替えようとしていますが、携帯電話のBluetoothを切断してもよろしいですか。",  	"SD 음악으로 전환할 예정입니다. 휴대폰 Bluetooth를 끊으시겠습니까?",  	"Sur le point de passer à SD Music, êtes - vous sûr de déconnecter le Bluetooth de votre téléphone?",  	"Ich schalte gerade auf SD-Musik um. Sind Sie sicher, dass Sie die Bluetooth-Verbindung meines Telefons trennen möchten?",  	"Скоро переключится на SD - музыку, точно ли отключить мобильный Bluetooth?",  	"¿A punto de cambiar a la música sd, ¿ está seguro de desconectar el Bluetooth del teléfono?",  	"Estou prestes a mudar para música SD. Tem a certeza que quer desligar o Bluetooth do meu telefone?",  	"Είμαι έτοιμος να αλλάξω μουσική Σίγουρα θέλετε να αποσυνδέσετε το Bluetooth του τηλεφώνου μου;",  	"Ik sta op het punt om over te schakelen naar SD-muziek. Weet je zeker dat je de Bluetooth-verbinding van mijn telefoon wilt verbreken?",  	"Jesteś pewien, że chcesz odłączyć Bluetooth mojego telefonu?",  	"Er du sikker på, at du vil afbryde min telefons Bluetooth?",  	"على وشك التبديل إلى التنمية المستدامة الموسيقى ، هل أنت متأكد من أنك تريد قطع بلوتوث ؟"},
{	"即将切换到手机音乐，是否确定连接手机蓝牙",  		"即將切換到手機音樂，是否確定連接手機藍牙",  	"About to switch to mobile music. Are you sure you want to connect to your phone's Bluetooth",  	"携帯電話の音楽に切り替えます。携帯電話のBluetoothに接続しているかどうかを確認します",  	"휴대 전화 음악으로 전환 예정, 휴대 전화 Bluetooth 연결 확인",  	"Sur le point de passer à la musique de votre téléphone, si vous êtes sûr de connecter votre téléphone Bluetooth",  	"Sind Sie sicher, dass Sie eine Verbindung zum Bluetooth-Gerät Ihres Telefons herstellen möchten?",  	"Скоро переключится на мобильную музыку, точно ли подключен мобильный Bluetooth",  	"¿Está a punto de cambiar a la música del teléfono, ¿ está seguro de conectarse al Bluetooth del teléfono?",  	"Está prestes a mudar para música móvel. Tem a certeza que pretende ligar-se ao Bluetooth do seu telemóvel",  	"Πρόκειται να μεταβείτε στη μουσική για κινητά. Είστε σίγουροι ότι θέλετε να συνδεθείτε στο τηλέφωνό σας",  	"Weet u zeker dat u verbinding wilt maken met de Bluetooth-verbinding van uw telefoon?",  	"Czy na pewno chcesz połączyć się z Bluetooth telefonu?",  	"Er du sikker på, at du vil oprette forbindelse til din telefons Bluetooth?",  	"على وشك التبديل إلى الهاتف المحمول الموسيقى ، هل أنت متأكد من أنك تريد الاتصال بلوتوث"},
{	"搜索超时",  		"蒐索超時",  	"Search Timeout ",  	"検索タイムアウト",  	"검색 시간 초과",  	"Recherche de Timeout",  	"Suchzeitüberschreitung",  	"Время ожидания поиска",  	"Horas extras de búsqueda",  	"Tempo- Limite da Pesquisa",  	"Χρονικό όριο αναζήτησης",  	"Tijdlimiet zoeken",  	"Czas wyszukiwania",  	"Søg Timeout",  	"مهلة البحث"},
{	"取消",  		"取消",  	"Canc",  	"キャン",  	"취소",  	"Annul",  	"Storn",  	"Отм",  	"Canc",  	"Canc",  	"Ακυρ",  	"Annul",  	"Anul",  	"Anul",  	"إلغ"},
{	"确定",  		"確定",  	"Conf",  	"確認",  	"확",  	"Conf",  	"Best",  	"Подт",  	"Conf",  	"Conf",  	"Επιβ",  	"Bev",  	"Potw",  	"Bekr",  	"تأك"},
{	"文件传输",  		"檔案傳輸",  	"File transfer",  	"ファイル転送",  	"파일 전송",  	"Transfert de fichiers",  	"Dateiübertragung",  	"Передача файлов",  	"Transmisión de archivos",  	"transferência de ficheiros",  	"μεταφορά αρχείων",  	"bestandsoverdracht",  	"transfer plików",  	"filoverførsel",  	"نقل الملفات"},
{	"请插入usb",  		"請插入usb",  	"Please insert USB",  	"usbを挿入してください",  	"usb 삽입",  	"Veuillez insérer l'USB",  	"Bitte USB einlegen",  	"Вставьте USB",  	"Por favor, introduzca USB",  	"Insira o USB",  	"Παρακαλώ εισάγετε USB",  	"Plaats USB",  	"Proszę włożyć USB",  	"Indsæt venligst USB",  	"الرجاء إدراج الناقل التسلسلي العام"},
{	"静噪",  		"靜噪",  	"Silence",  	"ざつおん",  	"정적 소음",  	"Bruit silencieux",  	"Stille",  	"Тишина",  	"Silencio",  	"Silêncio",  	"Σιωπή",  	"Stilte",  	"Cisza",  	"Stilhed",  	"كتم"},
{	"静噪中",  		"靜噪中",  	"In silence",  	"静音中",  	"정적 소음 중",  	"Dans le bruit silencieux",  	"In Stille",  	"В тишине",  	"En silencio",  	"Em silêncio",  	"Σε σιωπή",  	"In stilte",  	"W milczeniu",  	"I stilhed",  	"كتم"},
{	"设置",  		"設定",  	"Settings",  	"設定",  	"설치",  	"Param",  	"Einstell",  	"Настр",  	"Config",  	"Config",  	"Ρυθμισ",  	"Instell",  	"Ustawien",  	"Indstill",  	"إعدادا"},
{	"返回",  		"返回",  	"Return",  	"戻",  	"반환",  	"Ret",  	"Zurü",  	"Возв",  	"Reg",  	"Ret",  	"Επισ",  	"Teru",  	"Powr",  	"Tilb",  	"عود"},
{	"保存",  		"保存",  	"Save",  	"保存",  	"저장",  	"Sauv",  	"Spei",  	"Сохр",  	"Guar",  	"Salv",  	"Αποθ",  	"Opsl",  	"Zapisz",  	"Gemme ",  	"حفظ"},
{	"音量调节",  		"音量調節",  	"modulation",  	"音量調節",  	"볼륨 조절",  	"Réglage du volume",  	"Modulation",  	"Регулирование громкости",  	"Ajuste de volumen",  	"modulação",  	"διαφοροποίηση",  	"modulatie",  	"modulacja",  	"modulation",  	"ضبط حجم"},
{	"锁屏壁纸",  		"鎖屏桌面",  	"Lock screen wallpaper",  	"ロックスクリーン壁紙",  	"잠금 화면 벽지",  	"Lockscreen Fonds d'écran",  	"Bildschirmhintergrund sperren",  	"Обои с запирающим экраном",  	"Papel pintado de pantalla de bloqueo",  	"Bloquear o ecrã de papel de parede",  	"Ταπετσαρία κλειδώματος οθόνης",  	"Schermbeschermachtergrond vergrendelen",  	"Tapeta na ekranie blokady",  	"Lås skærm tapet",  	"قفل خلفية الشاشة"},
{	"今日功德",  		"今日功德",  	"Today's Merit",  	"今日の功徳",  	"오늘의 공덕",  	"Mérite aujourd'hui",  	"Der heutige Verdienst",  	"Ныне заслуги",  	"Méritos de hoy",  	"O Mérito de Hoje",  	"Η σημερινή Αξία",  	"De verdienste van vandaag",  	"Dzisiejsza zasługa",  	"Dagens fortjeneste",  	"الجدارة اليوم"},
{	"功德+1",  		"功德+1",  	"Merit+1",  	"功德+1",  	"공덕 +1",  	"Mérite + 1",  	"Verdienst+1",  	"Кунг - дэ + 1",  	"Mérito + 1",  	"Mérito+1",  	"Αξία+1",  	"Verdienste+1",  	"Zasługi+1",  	"Fortjeneste+1",  	"الجدارة + 1"},
{	"重复",  		"重複",  	"Repeat",  	"繰返",  	"반복",  	"Répét",  	"Wieder",  	"Повтр",  	"Repet",  	"Repet",  	"Επανα",  	"Herha",  	"Powt",  	"Genta",  	"تكرار"},
{	"停止",  		"停止",  	"Stop",  	"停止",  	"정지",  	"Arrêt",  	"Stop",  	"Стоп",  	"Parar",  	"Parar",  	"Διακο",  	"Stop",  	"Zatrz",  	"Stop",  	"توقف"},
{	"关闭",  		"關閉",  	"CLOSE",  	"CLOSE",  	"CLOSE",  	"FERM",  	"SCHL",  	"Закр",  	"CERR",  	"FECH",  	"Κλει",  	"SLUI",  	"ZAMK",  	"LUK",  	"إغل"},
{	"降噪",  		"降噪",  	"ANC",  	"ANC",  	"ANC",  	"RAB",  	"AGU",  	"АШП",  	"CAR",  	"CAR",  	"ΕΑΘ",  	"ARO",  	"ARS",  	"ASR",  	"إضن"},
{	"通透",  		"通透",  	"TRANS",  	"TRANS",  	"TRANS",  	"TRANS",  	"TRANS",  	"Проз",  	"TRANS",  	"TRANS",  	"Διαφ",  	"TRANS",  	"PRZEZ",  	"GENN",  	"شف"},
{	"开始",  		"開始",  	"Start",  	"開始",  	"시작",  	"Comm",  	"Start",  	"Начт.",  	"Empe",  	"Come",  	"Έναρ",  	"Begi",  	"Zacz",  	"Starte ",  	"بدء"},
{	"打开",  		"打開",  	"Open",  	"開く",  	"열기",  	"Ouvrir",  	"offen",  	"Открыть",  	"Abrir",  	"abrir",  	"ανοικτό",  	"open",  	"otwarty",  	"åben",  	"فتح ."},
{	"点赞",  		"點贊",  	"Like",  	"いいねを押す",  	"좋아요",  	"Un like",  	"Wie",  	"Похвалить",  	"Me gusta",  	"Como",  	"Όπως",  	"Zoals",  	"Jak na przykład",  	"Ligesom",  	"نقطة الثناء"},
{	"音乐",  		"音樂",  	"Music",  	"音楽 ",  	"음악",  	"Musique",  	"Musik ",  	"Mузыка ",  	"Música",  	"Música",  	"μουσική ",  	"Muziek",  	"Muzyka",  	"Musik",  	"الموسيقى "},
{	"音量",  		"音量",  	"Volume",  	"音量 ",  	"볼륨",  	"Volume",  	"Lautstärke",  	"Громкость ",  	"Volumen",  	"Volume",  	"Περιστροφή ήχου",  	"Volume",  	"Głośność",  	"Volumen",  	" مستوى الصوت"},
{	"亮度",  		"亮度",  	"Brightness",  	"輝度",  	"밝기",  	"Luminosité",  	"Helligkeit",  	"Яркость",  	"Brillo",  	"Brilho",  	"Φωτεινότητα",  	"Helderheid",  	"Jasność",  	"Lysstyrke",  	"ضوء"},
{	"语言",  		"語言",  	"Language",  	"語言",  	"언어",  	"Langue",  	"Sprache",  	"язык",  	"Lengua",  	"Linguagem",  	"Γλώσσα",  	"Taal",  	"Język",  	"Sprog",  	"لغة"},
{	"壁纸",  		"桌面",  	"Wallpaper",  	"壁紙",  	"벽지",  	"Papier peint",  	"Tapete",  	"Обои",  	"Papel pintado",  	"Papel de parede",  	"Βερνίκη",  	"Behang",  	"Tapeta",  	"Tapet",  	"ورق جدار"},
{	"抖音",  		"抖音",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok",  	"Tiktok"},
{	"查找耳机",  		"查找耳機",  	"Find my headphones",  	"イヤホン",  	"이어폰",  	"Casque",  	"Kopfhörer",  	"Наушники",  	"Auriculares",  	"Fones de ouvido",  	"Καρφιά",  	"Oordopjes",  	"Słuchawki",  	"Hovedtelefoner",  	"سماعات"},
{	"时钟",  		"時鐘",  	"Clock",  	"時計",  	"시계",  	"Horloge",  	"Uhr",  	"Часы",  	"Reloj",  	"Relógio",  	"Ρολόι",  	"Klok",  	"Zegar",  	"Ur",  	"ساعة"},
{	"拍照",  		"拍照",  	"Photograph",  	"写真を撮る",  	"사진을 찍다",  	"Prendre une photo",  	"Ein Foto machen",  	"Фотографировать",  	"Tomar una foto",  	"Tirar uma foto",  	"Βγάζω φωτογραφία",  	"Een foto maken",  	"Robić zdjęcie",  	"Tage et billede",  	"التقاط صورة"},
{	"木鱼",  		"木魚",  	"Woodenfish",  	"木魚",  	"목어",  	"poisson en bois",  	"Holzfisch",  	"деревянная рыба",  	"pez de madera",  	"peixe de madeira",  	"ξύλινο ψάρι",  	"houten vis",  	"drewniana ryba",  	"træfisk",  	"سمك خشبي"},
{	"%d分钟",  		"%d分鐘",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin",  	"%dMin"},
{	"天气",  		"天氣",  	"Weather",  	"天気",  	"날씨",  	"météo",  	"Wetter",  	"погода",  	"clima",  	"clima",  	"καιρός",  	"weer",  	"pogoda",  	"vejr",  	"الطقس"},
{   "关机",  	    "關機",     "Power Off",    "シャットダウン",   "컴퓨터 끄기",  "En mode veille",   "Mach das aus.",    "выключ",   "apagado",  "Desligado.",   "Peche",    "uitschakeling",    "Zamknięcia",   "Lukning",      "Power Off"},
{	"复位",  		"復位",  	"resetting",  	"リセットします",  	"제자리로",  	"remise",  	"Umschaltung.",  	"перезагрузк",  	"reanexar",  	"restauração",  	"Reposición",  	"terugsturen",  	"Zmienić położenie",  	"Flytte",  	"resetting"},
{	"重启",  		"重啓",  	"Restart",  	"再開します",  	"재개",  	"La reprise",  	"Reset.",  	"перезагрузк",  	"reiniciar",  	"reiniciar",  	"Relanzamento",  	"herstarten",  	"Ponowny rozruch",  	"Genstarte",  	"Restart"},
{	"简体中文",  		"繁體中文",  	"English",  	"日本語",  	"한국어",  	"Français",  	"Deutsch",  	"Русский язык",  	"Español",  	"Português",  	"Ελληνικά",  	"Nederlands",  	"Polski",  	"Dansk",  	"بالعربية"},
};



//  图片重映射表
const void * picMultilingualMap[][MULT_MAX] = {
    {   [M_CHINESE_SIMPLIFIED]="F:/ic_quxiao_chazhaoerji.bin", [M_ENGLISH]="F:/ic_quxiao_chazhaoerji_eng.bin"  },
    {               "F:/ic_guan_lianjie.bin",                   "F:/ic_guan_weilianjie.bin"              },
};



static int now_language = 0;
static u8 multilingual_remap_on = 1;

//  在lv_label_set_text_fmt
//  lv_label_set_text
void multilingual_text_remap(char ** strptr){
    if(!multilingual_remap_on)  return;

    char * str = *strptr;
    // printf(">>>str %x",str);
    if(str >= (char*)0x400000 && str <= (char*)0x800000){
        return;
    }

    for(int i=0; i<(sizeof(multilingualMap)/sizeof(multilingualMap[MULT_MAX])); i++){
        // printf("%s %s",multilingualMap[i][0], str);
        if(0 == strcmp(multilingualMap[i][DEFAULT_LANGUAGE], str)){
            *strptr = multilingualMap[i][now_language];
            // b_printf("%s %s", **strptr, *strptr);
            break;
        }
    }

}


void multilingual_pic_remap(void ** picptr){
    if(!multilingual_remap_on)  return;

    void  * src = *picptr;

    lv_img_src_t type = lv_img_src_get_type(src);

    if(src >= (char*)0x400000 && src <= (char*)0x800000){
        return;
    }

    if(LV_IMG_SRC_FILE == type){
        for(int i=0; i<(sizeof(picMultilingualMap)/sizeof(picMultilingualMap[MULT_MAX])); i++){
            if(0 == strcmp(picMultilingualMap[i][DEFAULT_LANGUAGE], src)){
                *picptr = picMultilingualMap[i][now_language];
                return;
            }
        }        
    }

    if(LV_IMG_SRC_VARIABLE == type){
        for(int i=0; i<(sizeof(picMultilingualMap)/sizeof(picMultilingualMap[MULT_MAX])); i++){
            if(picMultilingualMap[i][DEFAULT_LANGUAGE] == src){
                *picptr = picMultilingualMap[i][now_language];
                return;
            }
        }        
    }
}

int lv_set_language(int in){
    if(in<0 || in>=(sizeof(multilingualMap)/sizeof(multilingualMap[MULT_MAX]))){
        r_printf("SET LANGUAGE: %d ERROR", in);
        return -1;
    }
    now_language = in;
    return 0;
}

int lv_get_langauge()
{
    r_printf("LANGUAGE: %d", now_language);
    return now_language;
}

void multilingual_remap_enable(u8 on){
    multilingual_remap_on = on;
}


#endif