# file emoji.json from gtk+3 source
# `cat /gtk+-3/gtk/emoji/emoji.json | jq '.[]| .char + " " + .name' |sed 's/\(&\)/&amp;/;  s/"//g'`
# font: ttf-twemoji

emoji=$(t4 -n -l 40 <<End-of-message
😀 grinning face
😁 beaming face with smiling eyes
😂 face with tears of joy
🤣 rolling on the floor laughing
😃 grinning face with big eyes
😄 grinning face with smiling eyes
😅 grinning face with sweat
😆 grinning squinting face
😉 winking face
😊 smiling face with smiling eyes
😋 face savoring food
😎 smiling face with sunglasses
😍 smiling face with heart-eyes
😘 face blowing a kiss
😗 kissing face
😙 kissing face with smiling eyes
😚 kissing face with closed eyes
☺ smiling face
🙂 slightly smiling face
🤗 hugging face
🤩 ⊛ star-struck
🤔 thinking face
🤨 ⊛ face with raised eyebrow
😐 neutral face
😑 expressionless face
😶 face without mouth
🙄 face with rolling eyes
😏 smirking face
😣 persevering face
😥 sad but relieved face
😮 face with open mouth
🤐 zipper-mouth face
😯 hushed face
😪 sleepy face
😫 tired face
😴 sleeping face
😌 relieved face
😛 face with tongue
😜 winking face with tongue
😝 squinting face with tongue
🤤 drooling face
😒 unamused face
😓 downcast face with sweat
😔 pensive face
😕 confused face
🙃 upside-down face
🤑 money-mouth face
😲 astonished face
☹ frowning face
🙁 slightly frowning face
😖 confounded face
😞 disappointed face
😟 worried face
😤 face with steam from nose
😢 crying face
😭 loudly crying face
😦 frowning face with open mouth
😧 anguished face
😨 fearful face
😩 weary face
🤯 ⊛ exploding head
😬 grimacing face
😰 anxious face with sweat
😱 face screaming in fear
😳 flushed face
🤪 ⊛ crazy face
😵 dizzy face
😡 pouting face
😠 angry face
🤬 ⊛ face with symbols on mouth
😷 face with medical mask
🤒 face with thermometer
🤕 face with head-bandage
🤢 nauseated face
🤮 ⊛ face vomiting
🤧 sneezing face
😇 smiling face with halo
🤠 cowboy hat face
🤡 clown face
🤥 lying face
🤫 ⊛ shushing face
🤭 ⊛ face with hand over mouth
🧐 ⊛ face with monocle
🤓 nerd face
😈 smiling face with horns
👿 angry face with horns
👹 ogre
👺 goblin
💀 skull
☠ skull and crossbones
👻 ghost
👽 alien
👾 alien monster
🤖 robot face
💩 pile of poo
😺 grinning cat face
😸 grinning cat face with smiling eyes
😹 cat face with tears of joy
😻 smiling cat face with heart-eyes
😼 cat face with wry smile
😽 kissing cat face
🙀 weary cat face
😿 crying cat face
😾 pouting cat face
🙈 see-no-evil monkey
🙉 hear-no-evil monkey
🙊 speak-no-evil monkey
👶 baby
👶🏻 baby: light skin tone
👶🏼 baby: medium-light skin tone
👶🏽 baby: medium skin tone
👶🏾 baby: medium-dark skin tone
👶🏿 baby: dark skin tone
🧒 ⊛ child
🧒🏻 ⊛ child: light skin tone
🧒🏼 ⊛ child: medium-light skin tone
🧒🏽 ⊛ child: medium skin tone
🧒🏾 ⊛ child: medium-dark skin tone
🧒🏿 ⊛ child: dark skin tone
👦 boy
👦🏻 boy: light skin tone
👦🏼 boy: medium-light skin tone
👦🏽 boy: medium skin tone
👦🏾 boy: medium-dark skin tone
👦🏿 boy: dark skin tone
👧 girl
👧🏻 girl: light skin tone
👧🏼 girl: medium-light skin tone
👧🏽 girl: medium skin tone
👧🏾 girl: medium-dark skin tone
👧🏿 girl: dark skin tone
🧑 ⊛ adult
🧑🏻 ⊛ adult: light skin tone
🧑🏼 ⊛ adult: medium-light skin tone
🧑🏽 ⊛ adult: medium skin tone
🧑🏾 ⊛ adult: medium-dark skin tone
🧑🏿 ⊛ adult: dark skin tone
👨 man
👨🏻 man: light skin tone
👨🏼 man: medium-light skin tone
👨🏽 man: medium skin tone
👨🏾 man: medium-dark skin tone
👨🏿 man: dark skin tone
👩 woman
👩🏻 woman: light skin tone
👩🏼 woman: medium-light skin tone
👩🏽 woman: medium skin tone
👩🏾 woman: medium-dark skin tone
👩🏿 woman: dark skin tone
🧓 ⊛ older adult
🧓🏻 ⊛ older adult: light skin tone
🧓🏼 ⊛ older adult: medium-light skin tone
🧓🏽 ⊛ older adult: medium skin tone
🧓🏾 ⊛ older adult: medium-dark skin tone
🧓🏿 ⊛ older adult: dark skin tone
👴 old man
👴🏻 old man: light skin tone
👴🏼 old man: medium-light skin tone
👴🏽 old man: medium skin tone
👴🏾 old man: medium-dark skin tone
👴🏿 old man: dark skin tone
👵 old woman
👵🏻 old woman: light skin tone
👵🏼 old woman: medium-light skin tone
👵🏽 old woman: medium skin tone
👵🏾 old woman: medium-dark skin tone
👵🏿 old woman: dark skin tone
👨‍⚕️ man health worker
👨🏻‍⚕️ man health worker: light skin tone
👨🏼‍⚕️ man health worker: medium-light skin tone
👨🏽‍⚕️ man health worker: medium skin tone
👨🏾‍⚕️ man health worker: medium-dark skin tone
👨🏿‍⚕️ man health worker: dark skin tone
👩‍⚕️ woman health worker
👩🏻‍⚕️ woman health worker: light skin tone
👩🏼‍⚕️ woman health worker: medium-light skin tone
👩🏽‍⚕️ woman health worker: medium skin tone
👩🏾‍⚕️ woman health worker: medium-dark skin tone
👩🏿‍⚕️ woman health worker: dark skin tone
👨‍🎓 man student
👨🏻‍🎓 man student: light skin tone
👨🏼‍🎓 man student: medium-light skin tone
👨🏽‍🎓 man student: medium skin tone
👨🏾‍🎓 man student: medium-dark skin tone
👨🏿‍🎓 man student: dark skin tone
👩‍🎓 woman student
👩🏻‍🎓 woman student: light skin tone
👩🏼‍🎓 woman student: medium-light skin tone
👩🏽‍🎓 woman student: medium skin tone
👩🏾‍🎓 woman student: medium-dark skin tone
👩🏿‍🎓 woman student: dark skin tone
👨‍🏫 man teacher
👨🏻‍🏫 man teacher: light skin tone
👨🏼‍🏫 man teacher: medium-light skin tone
👨🏽‍🏫 man teacher: medium skin tone
👨🏾‍🏫 man teacher: medium-dark skin tone
👨🏿‍🏫 man teacher: dark skin tone
👩‍🏫 woman teacher
👩🏻‍🏫 woman teacher: light skin tone
👩🏼‍🏫 woman teacher: medium-light skin tone
👩🏽‍🏫 woman teacher: medium skin tone
👩🏾‍🏫 woman teacher: medium-dark skin tone
👩🏿‍🏫 woman teacher: dark skin tone
👨‍⚖️ man judge
👨🏻‍⚖️ man judge: light skin tone
👨🏼‍⚖️ man judge: medium-light skin tone
👨🏽‍⚖️ man judge: medium skin tone
👨🏾‍⚖️ man judge: medium-dark skin tone
👨🏿‍⚖️ man judge: dark skin tone
👩‍⚖️ woman judge
👩🏻‍⚖️ woman judge: light skin tone
👩🏼‍⚖️ woman judge: medium-light skin tone
👩🏽‍⚖️ woman judge: medium skin tone
👩🏾‍⚖️ woman judge: medium-dark skin tone
👩🏿‍⚖️ woman judge: dark skin tone
👨‍🌾 man farmer
👨🏻‍🌾 man farmer: light skin tone
👨🏼‍🌾 man farmer: medium-light skin tone
👨🏽‍🌾 man farmer: medium skin tone
👨🏾‍🌾 man farmer: medium-dark skin tone
👨🏿‍🌾 man farmer: dark skin tone
👩‍🌾 woman farmer
👩🏻‍🌾 woman farmer: light skin tone
👩🏼‍🌾 woman farmer: medium-light skin tone
👩🏽‍🌾 woman farmer: medium skin tone
👩🏾‍🌾 woman farmer: medium-dark skin tone
👩🏿‍🌾 woman farmer: dark skin tone
👨‍🍳 man cook
👨🏻‍🍳 man cook: light skin tone
👨🏼‍🍳 man cook: medium-light skin tone
👨🏽‍🍳 man cook: medium skin tone
👨🏾‍🍳 man cook: medium-dark skin tone
👨🏿‍🍳 man cook: dark skin tone
👩‍🍳 woman cook
👩🏻‍🍳 woman cook: light skin tone
👩🏼‍🍳 woman cook: medium-light skin tone
👩🏽‍🍳 woman cook: medium skin tone
👩🏾‍🍳 woman cook: medium-dark skin tone
👩🏿‍🍳 woman cook: dark skin tone
👨‍🔧 man mechanic
👨🏻‍🔧 man mechanic: light skin tone
👨🏼‍🔧 man mechanic: medium-light skin tone
👨🏽‍🔧 man mechanic: medium skin tone
👨🏾‍🔧 man mechanic: medium-dark skin tone
👨🏿‍🔧 man mechanic: dark skin tone
👩‍🔧 woman mechanic
👩🏻‍🔧 woman mechanic: light skin tone
👩🏼‍🔧 woman mechanic: medium-light skin tone
👩🏽‍🔧 woman mechanic: medium skin tone
👩🏾‍🔧 woman mechanic: medium-dark skin tone
👩🏿‍🔧 woman mechanic: dark skin tone
👨‍🏭 man factory worker
👨🏻‍🏭 man factory worker: light skin tone
👨🏼‍🏭 man factory worker: medium-light skin tone
👨🏽‍🏭 man factory worker: medium skin tone
👨🏾‍🏭 man factory worker: medium-dark skin tone
👨🏿‍🏭 man factory worker: dark skin tone
👩‍🏭 woman factory worker
👩🏻‍🏭 woman factory worker: light skin tone
👩🏼‍🏭 woman factory worker: medium-light skin tone
👩🏽‍🏭 woman factory worker: medium skin tone
👩🏾‍🏭 woman factory worker: medium-dark skin tone
👩🏿‍🏭 woman factory worker: dark skin tone
👨‍💼 man office worker
👨🏻‍💼 man office worker: light skin tone
👨🏼‍💼 man office worker: medium-light skin tone
👨🏽‍💼 man office worker: medium skin tone
👨🏾‍💼 man office worker: medium-dark skin tone
👨🏿‍💼 man office worker: dark skin tone
👩‍💼 woman office worker
👩🏻‍💼 woman office worker: light skin tone
👩🏼‍💼 woman office worker: medium-light skin tone
👩🏽‍💼 woman office worker: medium skin tone
👩🏾‍💼 woman office worker: medium-dark skin tone
👩🏿‍💼 woman office worker: dark skin tone
👨‍🔬 man scientist
👨🏻‍🔬 man scientist: light skin tone
👨🏼‍🔬 man scientist: medium-light skin tone
👨🏽‍🔬 man scientist: medium skin tone
👨🏾‍🔬 man scientist: medium-dark skin tone
👨🏿‍🔬 man scientist: dark skin tone
👩‍🔬 woman scientist
👩🏻‍🔬 woman scientist: light skin tone
👩🏼‍🔬 woman scientist: medium-light skin tone
👩🏽‍🔬 woman scientist: medium skin tone
👩🏾‍🔬 woman scientist: medium-dark skin tone
👩🏿‍🔬 woman scientist: dark skin tone
👨‍💻 man technologist
👨🏻‍💻 man technologist: light skin tone
👨🏼‍💻 man technologist: medium-light skin tone
👨🏽‍💻 man technologist: medium skin tone
👨🏾‍💻 man technologist: medium-dark skin tone
👨🏿‍💻 man technologist: dark skin tone
👩‍💻 woman technologist
👩🏻‍💻 woman technologist: light skin tone
👩🏼‍💻 woman technologist: medium-light skin tone
👩🏽‍💻 woman technologist: medium skin tone
👩🏾‍💻 woman technologist: medium-dark skin tone
👩🏿‍💻 woman technologist: dark skin tone
👨‍🎤 man singer
👨🏻‍🎤 man singer: light skin tone
👨🏼‍🎤 man singer: medium-light skin tone
👨🏽‍🎤 man singer: medium skin tone
👨🏾‍🎤 man singer: medium-dark skin tone
👨🏿‍🎤 man singer: dark skin tone
👩‍🎤 woman singer
👩🏻‍🎤 woman singer: light skin tone
👩🏼‍🎤 woman singer: medium-light skin tone
👩🏽‍🎤 woman singer: medium skin tone
👩🏾‍🎤 woman singer: medium-dark skin tone
👩🏿‍🎤 woman singer: dark skin tone
👨‍🎨 man artist
👨🏻‍🎨 man artist: light skin tone
👨🏼‍🎨 man artist: medium-light skin tone
👨🏽‍🎨 man artist: medium skin tone
👨🏾‍🎨 man artist: medium-dark skin tone
👨🏿‍🎨 man artist: dark skin tone
👩‍🎨 woman artist
👩🏻‍🎨 woman artist: light skin tone
👩🏼‍🎨 woman artist: medium-light skin tone
👩🏽‍🎨 woman artist: medium skin tone
👩🏾‍🎨 woman artist: medium-dark skin tone
👩🏿‍🎨 woman artist: dark skin tone
👨‍✈️ man pilot
👨🏻‍✈️ man pilot: light skin tone
👨🏼‍✈️ man pilot: medium-light skin tone
👨🏽‍✈️ man pilot: medium skin tone
👨🏾‍✈️ man pilot: medium-dark skin tone
👨🏿‍✈️ man pilot: dark skin tone
👩‍✈️ woman pilot
👩🏻‍✈️ woman pilot: light skin tone
👩🏼‍✈️ woman pilot: medium-light skin tone
👩🏽‍✈️ woman pilot: medium skin tone
👩🏾‍✈️ woman pilot: medium-dark skin tone
👩🏿‍✈️ woman pilot: dark skin tone
👨‍🚀 man astronaut
👨🏻‍🚀 man astronaut: light skin tone
👨🏼‍🚀 man astronaut: medium-light skin tone
👨🏽‍🚀 man astronaut: medium skin tone
👨🏾‍🚀 man astronaut: medium-dark skin tone
👨🏿‍🚀 man astronaut: dark skin tone
👩‍🚀 woman astronaut
👩🏻‍🚀 woman astronaut: light skin tone
👩🏼‍🚀 woman astronaut: medium-light skin tone
👩🏽‍🚀 woman astronaut: medium skin tone
👩🏾‍🚀 woman astronaut: medium-dark skin tone
👩🏿‍🚀 woman astronaut: dark skin tone
👨‍🚒 man firefighter
👨🏻‍🚒 man firefighter: light skin tone
👨🏼‍🚒 man firefighter: medium-light skin tone
👨🏽‍🚒 man firefighter: medium skin tone
👨🏾‍🚒 man firefighter: medium-dark skin tone
👨🏿‍🚒 man firefighter: dark skin tone
👩‍🚒 woman firefighter
👩🏻‍🚒 woman firefighter: light skin tone
👩🏼‍🚒 woman firefighter: medium-light skin tone
👩🏽‍🚒 woman firefighter: medium skin tone
👩🏾‍🚒 woman firefighter: medium-dark skin tone
👩🏿‍🚒 woman firefighter: dark skin tone
👮 police officer
👮🏻 police officer: light skin tone
👮🏼 police officer: medium-light skin tone
👮🏽 police officer: medium skin tone
👮🏾 police officer: medium-dark skin tone
👮🏿 police officer: dark skin tone
👮‍♂️ man police officer
👮🏻‍♂️ man police officer: light skin tone
👮🏼‍♂️ man police officer: medium-light skin tone
👮🏽‍♂️ man police officer: medium skin tone
👮🏾‍♂️ man police officer: medium-dark skin tone
👮🏿‍♂️ man police officer: dark skin tone
👮‍♀️ woman police officer
👮🏻‍♀️ woman police officer: light skin tone
👮🏼‍♀️ woman police officer: medium-light skin tone
👮🏽‍♀️ woman police officer: medium skin tone
👮🏾‍♀️ woman police officer: medium-dark skin tone
👮🏿‍♀️ woman police officer: dark skin tone
🕵 detective
🕵🏻 detective: light skin tone
🕵🏼 detective: medium-light skin tone
🕵🏽 detective: medium skin tone
🕵🏾 detective: medium-dark skin tone
🕵🏿 detective: dark skin tone
🕵️‍♂️ man detective
🕵🏻‍♂️ man detective: light skin tone
🕵🏼‍♂️ man detective: medium-light skin tone
🕵🏽‍♂️ man detective: medium skin tone
🕵🏾‍♂️ man detective: medium-dark skin tone
🕵🏿‍♂️ man detective: dark skin tone
🕵️‍♀️ woman detective
🕵🏻‍♀️ woman detective: light skin tone
🕵🏼‍♀️ woman detective: medium-light skin tone
🕵🏽‍♀️ woman detective: medium skin tone
🕵🏾‍♀️ woman detective: medium-dark skin tone
🕵🏿‍♀️ woman detective: dark skin tone
💂 guard
💂🏻 guard: light skin tone
💂🏼 guard: medium-light skin tone
💂🏽 guard: medium skin tone
💂🏾 guard: medium-dark skin tone
💂🏿 guard: dark skin tone
💂‍♂️ man guard
💂🏻‍♂️ man guard: light skin tone
💂🏼‍♂️ man guard: medium-light skin tone
💂🏽‍♂️ man guard: medium skin tone
💂🏾‍♂️ man guard: medium-dark skin tone
💂🏿‍♂️ man guard: dark skin tone
💂‍♀️ woman guard
💂🏻‍♀️ woman guard: light skin tone
💂🏼‍♀️ woman guard: medium-light skin tone
💂🏽‍♀️ woman guard: medium skin tone
💂🏾‍♀️ woman guard: medium-dark skin tone
💂🏿‍♀️ woman guard: dark skin tone
👷 construction worker
👷🏻 construction worker: light skin tone
👷🏼 construction worker: medium-light skin tone
👷🏽 construction worker: medium skin tone
👷🏾 construction worker: medium-dark skin tone
👷🏿 construction worker: dark skin tone
👷‍♂️ man construction worker
👷🏻‍♂️ man construction worker: light skin tone
👷🏼‍♂️ man construction worker: medium-light skin tone
👷🏽‍♂️ man construction worker: medium skin tone
👷🏾‍♂️ man construction worker: medium-dark skin tone
👷🏿‍♂️ man construction worker: dark skin tone
👷‍♀️ woman construction worker
👷🏻‍♀️ woman construction worker: light skin tone
👷🏼‍♀️ woman construction worker: medium-light skin tone
👷🏽‍♀️ woman construction worker: medium skin tone
👷🏾‍♀️ woman construction worker: medium-dark skin tone
👷🏿‍♀️ woman construction worker: dark skin tone
🤴 prince
🤴🏻 prince: light skin tone
🤴🏼 prince: medium-light skin tone
🤴🏽 prince: medium skin tone
🤴🏾 prince: medium-dark skin tone
🤴🏿 prince: dark skin tone
👸 princess
👸🏻 princess: light skin tone
👸🏼 princess: medium-light skin tone
👸🏽 princess: medium skin tone
👸🏾 princess: medium-dark skin tone
👸🏿 princess: dark skin tone
👳 person wearing turban
👳🏻 person wearing turban: light skin tone
👳🏼 person wearing turban: medium-light skin tone
👳🏽 person wearing turban: medium skin tone
👳🏾 person wearing turban: medium-dark skin tone
👳🏿 person wearing turban: dark skin tone
👳‍♂️ man wearing turban
👳🏻‍♂️ man wearing turban: light skin tone
👳🏼‍♂️ man wearing turban: medium-light skin tone
👳🏽‍♂️ man wearing turban: medium skin tone
👳🏾‍♂️ man wearing turban: medium-dark skin tone
👳🏿‍♂️ man wearing turban: dark skin tone
👳‍♀️ woman wearing turban
👳🏻‍♀️ woman wearing turban: light skin tone
👳🏼‍♀️ woman wearing turban: medium-light skin tone
👳🏽‍♀️ woman wearing turban: medium skin tone
👳🏾‍♀️ woman wearing turban: medium-dark skin tone
👳🏿‍♀️ woman wearing turban: dark skin tone
👲 man with Chinese cap
👲🏻 man with Chinese cap: light skin tone
👲🏼 man with Chinese cap: medium-light skin tone
👲🏽 man with Chinese cap: medium skin tone
👲🏾 man with Chinese cap: medium-dark skin tone
👲🏿 man with Chinese cap: dark skin tone
🧕 ⊛ woman with headscarf
🧕🏻 ⊛ woman with headscarf: light skin tone
🧕🏼 ⊛ woman with headscarf: medium-light skin tone
🧕🏽 ⊛ woman with headscarf: medium skin tone
🧕🏾 ⊛ woman with headscarf: medium-dark skin tone
🧕🏿 ⊛ woman with headscarf: dark skin tone
🧔 ⊛ bearded person
🧔🏻 ⊛ bearded person: light skin tone
🧔🏼 ⊛ bearded person: medium-light skin tone
🧔🏽 ⊛ bearded person: medium skin tone
🧔🏾 ⊛ bearded person: medium-dark skin tone
🧔🏿 ⊛ bearded person: dark skin tone
👱 blond-haired person
👱🏻 blond-haired person: light skin tone
👱🏼 blond-haired person: medium-light skin tone
👱🏽 blond-haired person: medium skin tone
👱🏾 blond-haired person: medium-dark skin tone
👱🏿 blond-haired person: dark skin tone
👱‍♂️ blond-haired man
👱🏻‍♂️ blond-haired man: light skin tone
👱🏼‍♂️ blond-haired man: medium-light skin tone
👱🏽‍♂️ blond-haired man: medium skin tone
👱🏾‍♂️ blond-haired man: medium-dark skin tone
👱🏿‍♂️ blond-haired man: dark skin tone
👱‍♀️ blond-haired woman
👱🏻‍♀️ blond-haired woman: light skin tone
👱🏼‍♀️ blond-haired woman: medium-light skin tone
👱🏽‍♀️ blond-haired woman: medium skin tone
👱🏾‍♀️ blond-haired woman: medium-dark skin tone
👱🏿‍♀️ blond-haired woman: dark skin tone
🤵 man in tuxedo
🤵🏻 man in tuxedo: light skin tone
🤵🏼 man in tuxedo: medium-light skin tone
🤵🏽 man in tuxedo: medium skin tone
🤵🏾 man in tuxedo: medium-dark skin tone
🤵🏿 man in tuxedo: dark skin tone
👰 bride with veil
👰🏻 bride with veil: light skin tone
👰🏼 bride with veil: medium-light skin tone
👰🏽 bride with veil: medium skin tone
👰🏾 bride with veil: medium-dark skin tone
👰🏿 bride with veil: dark skin tone
🤰 pregnant woman
🤰🏻 pregnant woman: light skin tone
🤰🏼 pregnant woman: medium-light skin tone
🤰🏽 pregnant woman: medium skin tone
🤰🏾 pregnant woman: medium-dark skin tone
🤰🏿 pregnant woman: dark skin tone
🤱 ⊛ breast-feeding
🤱🏻 ⊛ breast-feeding: light skin tone
🤱🏼 ⊛ breast-feeding: medium-light skin tone
🤱🏽 ⊛ breast-feeding: medium skin tone
🤱🏾 ⊛ breast-feeding: medium-dark skin tone
🤱🏿 ⊛ breast-feeding: dark skin tone
👼 baby angel
👼🏻 baby angel: light skin tone
👼🏼 baby angel: medium-light skin tone
👼🏽 baby angel: medium skin tone
👼🏾 baby angel: medium-dark skin tone
👼🏿 baby angel: dark skin tone
🎅 Santa Claus
🎅🏻 Santa Claus: light skin tone
🎅🏼 Santa Claus: medium-light skin tone
🎅🏽 Santa Claus: medium skin tone
🎅🏾 Santa Claus: medium-dark skin tone
🎅🏿 Santa Claus: dark skin tone
🤶 Mrs. Claus
🤶🏻 Mrs. Claus: light skin tone
🤶🏼 Mrs. Claus: medium-light skin tone
🤶🏽 Mrs. Claus: medium skin tone
🤶🏾 Mrs. Claus: medium-dark skin tone
🤶🏿 Mrs. Claus: dark skin tone
🧙 ⊛ mage
🧙🏻 ⊛ mage: light skin tone
🧙🏼 ⊛ mage: medium-light skin tone
🧙🏽 ⊛ mage: medium skin tone
🧙🏾 ⊛ mage: medium-dark skin tone
🧙🏿 ⊛ mage: dark skin tone
🧙‍♀️ ⊛ woman mage
🧙🏻‍♀️ ⊛ woman mage: light skin tone
🧙🏼‍♀️ ⊛ woman mage: medium-light skin tone
🧙🏽‍♀️ ⊛ woman mage: medium skin tone
🧙🏾‍♀️ ⊛ woman mage: medium-dark skin tone
🧙🏿‍♀️ ⊛ woman mage: dark skin tone
🧙‍♂️ ⊛ man mage
🧙🏻‍♂️ ⊛ man mage: light skin tone
🧙🏼‍♂️ ⊛ man mage: medium-light skin tone
🧙🏽‍♂️ ⊛ man mage: medium skin tone
🧙🏾‍♂️ ⊛ man mage: medium-dark skin tone
🧙🏿‍♂️ ⊛ man mage: dark skin tone
🧚 ⊛ fairy
🧚🏻 ⊛ fairy: light skin tone
🧚🏼 ⊛ fairy: medium-light skin tone
🧚🏽 ⊛ fairy: medium skin tone
🧚🏾 ⊛ fairy: medium-dark skin tone
🧚🏿 ⊛ fairy: dark skin tone
🧚‍♀️ ⊛ woman fairy
🧚🏻‍♀️ ⊛ woman fairy: light skin tone
🧚🏼‍♀️ ⊛ woman fairy: medium-light skin tone
🧚🏽‍♀️ ⊛ woman fairy: medium skin tone
🧚🏾‍♀️ ⊛ woman fairy: medium-dark skin tone
🧚🏿‍♀️ ⊛ woman fairy: dark skin tone
🧚‍♂️ ⊛ man fairy
🧚🏻‍♂️ ⊛ man fairy: light skin tone
🧚🏼‍♂️ ⊛ man fairy: medium-light skin tone
🧚🏽‍♂️ ⊛ man fairy: medium skin tone
🧚🏾‍♂️ ⊛ man fairy: medium-dark skin tone
🧚🏿‍♂️ ⊛ man fairy: dark skin tone
🧛 ⊛ vampire
🧛🏻 ⊛ vampire: light skin tone
🧛🏼 ⊛ vampire: medium-light skin tone
🧛🏽 ⊛ vampire: medium skin tone
🧛🏾 ⊛ vampire: medium-dark skin tone
🧛🏿 ⊛ vampire: dark skin tone
🧛‍♀️ ⊛ woman vampire
🧛🏻‍♀️ ⊛ woman vampire: light skin tone
🧛🏼‍♀️ ⊛ woman vampire: medium-light skin tone
🧛🏽‍♀️ ⊛ woman vampire: medium skin tone
🧛🏾‍♀️ ⊛ woman vampire: medium-dark skin tone
🧛🏿‍♀️ ⊛ woman vampire: dark skin tone
🧛‍♂️ ⊛ man vampire
🧛🏻‍♂️ ⊛ man vampire: light skin tone
🧛🏼‍♂️ ⊛ man vampire: medium-light skin tone
🧛🏽‍♂️ ⊛ man vampire: medium skin tone
🧛🏾‍♂️ ⊛ man vampire: medium-dark skin tone
🧛🏿‍♂️ ⊛ man vampire: dark skin tone
🧜 ⊛ merperson
🧜🏻 ⊛ merperson: light skin tone
🧜🏼 ⊛ merperson: medium-light skin tone
🧜🏽 ⊛ merperson: medium skin tone
🧜🏾 ⊛ merperson: medium-dark skin tone
🧜🏿 ⊛ merperson: dark skin tone
🧜‍♀️ ⊛ mermaid
🧜🏻‍♀️ ⊛ mermaid: light skin tone
🧜🏼‍♀️ ⊛ mermaid: medium-light skin tone
🧜🏽‍♀️ ⊛ mermaid: medium skin tone
🧜🏾‍♀️ ⊛ mermaid: medium-dark skin tone
🧜🏿‍♀️ ⊛ mermaid: dark skin tone
🧜‍♂️ ⊛ merman
🧜🏻‍♂️ ⊛ merman: light skin tone
🧜🏼‍♂️ ⊛ merman: medium-light skin tone
🧜🏽‍♂️ ⊛ merman: medium skin tone
🧜🏾‍♂️ ⊛ merman: medium-dark skin tone
🧜🏿‍♂️ ⊛ merman: dark skin tone
🧝 ⊛ elf
🧝🏻 ⊛ elf: light skin tone
🧝🏼 ⊛ elf: medium-light skin tone
🧝🏽 ⊛ elf: medium skin tone
🧝🏾 ⊛ elf: medium-dark skin tone
🧝🏿 ⊛ elf: dark skin tone
🧝‍♀️ ⊛ woman elf
🧝🏻‍♀️ ⊛ woman elf: light skin tone
🧝🏼‍♀️ ⊛ woman elf: medium-light skin tone
🧝🏽‍♀️ ⊛ woman elf: medium skin tone
🧝🏾‍♀️ ⊛ woman elf: medium-dark skin tone
🧝🏿‍♀️ ⊛ woman elf: dark skin tone
🧝‍♂️ ⊛ man elf
🧝🏻‍♂️ ⊛ man elf: light skin tone
🧝🏼‍♂️ ⊛ man elf: medium-light skin tone
🧝🏽‍♂️ ⊛ man elf: medium skin tone
🧝🏾‍♂️ ⊛ man elf: medium-dark skin tone
🧝🏿‍♂️ ⊛ man elf: dark skin tone
🧞 ⊛ genie
🧞‍♀️ ⊛ woman genie
🧞‍♂️ ⊛ man genie
🧟 ⊛ zombie
🧟‍♀️ ⊛ woman zombie
🧟‍♂️ ⊛ man zombie
🙍 person frowning
🙍🏻 person frowning: light skin tone
🙍🏼 person frowning: medium-light skin tone
🙍🏽 person frowning: medium skin tone
🙍🏾 person frowning: medium-dark skin tone
🙍🏿 person frowning: dark skin tone
🙍‍♂️ man frowning
🙍🏻‍♂️ man frowning: light skin tone
🙍🏼‍♂️ man frowning: medium-light skin tone
🙍🏽‍♂️ man frowning: medium skin tone
🙍🏾‍♂️ man frowning: medium-dark skin tone
🙍🏿‍♂️ man frowning: dark skin tone
🙍‍♀️ woman frowning
🙍🏻‍♀️ woman frowning: light skin tone
🙍🏼‍♀️ woman frowning: medium-light skin tone
🙍🏽‍♀️ woman frowning: medium skin tone
🙍🏾‍♀️ woman frowning: medium-dark skin tone
🙍🏿‍♀️ woman frowning: dark skin tone
🙎 person pouting
🙎🏻 person pouting: light skin tone
🙎🏼 person pouting: medium-light skin tone
🙎🏽 person pouting: medium skin tone
🙎🏾 person pouting: medium-dark skin tone
🙎🏿 person pouting: dark skin tone
🙎‍♂️ man pouting
🙎🏻‍♂️ man pouting: light skin tone
🙎🏼‍♂️ man pouting: medium-light skin tone
🙎🏽‍♂️ man pouting: medium skin tone
🙎🏾‍♂️ man pouting: medium-dark skin tone
🙎🏿‍♂️ man pouting: dark skin tone
🙎‍♀️ woman pouting
🙎🏻‍♀️ woman pouting: light skin tone
🙎🏼‍♀️ woman pouting: medium-light skin tone
🙎🏽‍♀️ woman pouting: medium skin tone
🙎🏾‍♀️ woman pouting: medium-dark skin tone
🙎🏿‍♀️ woman pouting: dark skin tone
🙅 person gesturing NO
🙅🏻 person gesturing NO: light skin tone
🙅🏼 person gesturing NO: medium-light skin tone
🙅🏽 person gesturing NO: medium skin tone
🙅🏾 person gesturing NO: medium-dark skin tone
🙅🏿 person gesturing NO: dark skin tone
🙅‍♂️ man gesturing NO
🙅🏻‍♂️ man gesturing NO: light skin tone
🙅🏼‍♂️ man gesturing NO: medium-light skin tone
🙅🏽‍♂️ man gesturing NO: medium skin tone
🙅🏾‍♂️ man gesturing NO: medium-dark skin tone
🙅🏿‍♂️ man gesturing NO: dark skin tone
🙅‍♀️ woman gesturing NO
🙅🏻‍♀️ woman gesturing NO: light skin tone
🙅🏼‍♀️ woman gesturing NO: medium-light skin tone
🙅🏽‍♀️ woman gesturing NO: medium skin tone
🙅🏾‍♀️ woman gesturing NO: medium-dark skin tone
🙅🏿‍♀️ woman gesturing NO: dark skin tone
🙆 person gesturing OK
🙆🏻 person gesturing OK: light skin tone
🙆🏼 person gesturing OK: medium-light skin tone
🙆🏽 person gesturing OK: medium skin tone
🙆🏾 person gesturing OK: medium-dark skin tone
🙆🏿 person gesturing OK: dark skin tone
🙆‍♂️ man gesturing OK
🙆🏻‍♂️ man gesturing OK: light skin tone
🙆🏼‍♂️ man gesturing OK: medium-light skin tone
🙆🏽‍♂️ man gesturing OK: medium skin tone
🙆🏾‍♂️ man gesturing OK: medium-dark skin tone
🙆🏿‍♂️ man gesturing OK: dark skin tone
🙆‍♀️ woman gesturing OK
🙆🏻‍♀️ woman gesturing OK: light skin tone
🙆🏼‍♀️ woman gesturing OK: medium-light skin tone
🙆🏽‍♀️ woman gesturing OK: medium skin tone
🙆🏾‍♀️ woman gesturing OK: medium-dark skin tone
🙆🏿‍♀️ woman gesturing OK: dark skin tone
💁 person tipping hand
💁🏻 person tipping hand: light skin tone
💁🏼 person tipping hand: medium-light skin tone
💁🏽 person tipping hand: medium skin tone
💁🏾 person tipping hand: medium-dark skin tone
💁🏿 person tipping hand: dark skin tone
💁‍♂️ man tipping hand
💁🏻‍♂️ man tipping hand: light skin tone
💁🏼‍♂️ man tipping hand: medium-light skin tone
💁🏽‍♂️ man tipping hand: medium skin tone
💁🏾‍♂️ man tipping hand: medium-dark skin tone
💁🏿‍♂️ man tipping hand: dark skin tone
💁‍♀️ woman tipping hand
💁🏻‍♀️ woman tipping hand: light skin tone
💁🏼‍♀️ woman tipping hand: medium-light skin tone
💁🏽‍♀️ woman tipping hand: medium skin tone
💁🏾‍♀️ woman tipping hand: medium-dark skin tone
💁🏿‍♀️ woman tipping hand: dark skin tone
🙋 person raising hand
🙋🏻 person raising hand: light skin tone
🙋🏼 person raising hand: medium-light skin tone
🙋🏽 person raising hand: medium skin tone
🙋🏾 person raising hand: medium-dark skin tone
🙋🏿 person raising hand: dark skin tone
🙋‍♂️ man raising hand
🙋🏻‍♂️ man raising hand: light skin tone
🙋🏼‍♂️ man raising hand: medium-light skin tone
🙋🏽‍♂️ man raising hand: medium skin tone
🙋🏾‍♂️ man raising hand: medium-dark skin tone
🙋🏿‍♂️ man raising hand: dark skin tone
🙋‍♀️ woman raising hand
🙋🏻‍♀️ woman raising hand: light skin tone
🙋🏼‍♀️ woman raising hand: medium-light skin tone
🙋🏽‍♀️ woman raising hand: medium skin tone
🙋🏾‍♀️ woman raising hand: medium-dark skin tone
🙋🏿‍♀️ woman raising hand: dark skin tone
🙇 person bowing
🙇🏻 person bowing: light skin tone
🙇🏼 person bowing: medium-light skin tone
🙇🏽 person bowing: medium skin tone
🙇🏾 person bowing: medium-dark skin tone
🙇🏿 person bowing: dark skin tone
🙇‍♂️ man bowing
🙇🏻‍♂️ man bowing: light skin tone
🙇🏼‍♂️ man bowing: medium-light skin tone
🙇🏽‍♂️ man bowing: medium skin tone
🙇🏾‍♂️ man bowing: medium-dark skin tone
🙇🏿‍♂️ man bowing: dark skin tone
🙇‍♀️ woman bowing
🙇🏻‍♀️ woman bowing: light skin tone
🙇🏼‍♀️ woman bowing: medium-light skin tone
🙇🏽‍♀️ woman bowing: medium skin tone
🙇🏾‍♀️ woman bowing: medium-dark skin tone
🙇🏿‍♀️ woman bowing: dark skin tone
🤦 person facepalming
🤦🏻 person facepalming: light skin tone
🤦🏼 person facepalming: medium-light skin tone
🤦🏽 person facepalming: medium skin tone
🤦🏾 person facepalming: medium-dark skin tone
🤦🏿 person facepalming: dark skin tone
🤦‍♂️ man facepalming
🤦🏻‍♂️ man facepalming: light skin tone
🤦🏼‍♂️ man facepalming: medium-light skin tone
🤦🏽‍♂️ man facepalming: medium skin tone
🤦🏾‍♂️ man facepalming: medium-dark skin tone
🤦🏿‍♂️ man facepalming: dark skin tone
🤦‍♀️ woman facepalming
🤦🏻‍♀️ woman facepalming: light skin tone
🤦🏼‍♀️ woman facepalming: medium-light skin tone
🤦🏽‍♀️ woman facepalming: medium skin tone
🤦🏾‍♀️ woman facepalming: medium-dark skin tone
🤦🏿‍♀️ woman facepalming: dark skin tone
🤷 person shrugging
🤷🏻 person shrugging: light skin tone
🤷🏼 person shrugging: medium-light skin tone
🤷🏽 person shrugging: medium skin tone
🤷🏾 person shrugging: medium-dark skin tone
🤷🏿 person shrugging: dark skin tone
🤷‍♂️ man shrugging
🤷🏻‍♂️ man shrugging: light skin tone
🤷🏼‍♂️ man shrugging: medium-light skin tone
🤷🏽‍♂️ man shrugging: medium skin tone
🤷🏾‍♂️ man shrugging: medium-dark skin tone
🤷🏿‍♂️ man shrugging: dark skin tone
🤷‍♀️ woman shrugging
🤷🏻‍♀️ woman shrugging: light skin tone
🤷🏼‍♀️ woman shrugging: medium-light skin tone
🤷🏽‍♀️ woman shrugging: medium skin tone
🤷🏾‍♀️ woman shrugging: medium-dark skin tone
🤷🏿‍♀️ woman shrugging: dark skin tone
💆 person getting massage
💆🏻 person getting massage: light skin tone
💆🏼 person getting massage: medium-light skin tone
💆🏽 person getting massage: medium skin tone
💆🏾 person getting massage: medium-dark skin tone
💆🏿 person getting massage: dark skin tone
💆‍♂️ man getting massage
💆🏻‍♂️ man getting massage: light skin tone
💆🏼‍♂️ man getting massage: medium-light skin tone
💆🏽‍♂️ man getting massage: medium skin tone
💆🏾‍♂️ man getting massage: medium-dark skin tone
💆🏿‍♂️ man getting massage: dark skin tone
💆‍♀️ woman getting massage
💆🏻‍♀️ woman getting massage: light skin tone
💆🏼‍♀️ woman getting massage: medium-light skin tone
💆🏽‍♀️ woman getting massage: medium skin tone
💆🏾‍♀️ woman getting massage: medium-dark skin tone
💆🏿‍♀️ woman getting massage: dark skin tone
💇 person getting haircut
💇🏻 person getting haircut: light skin tone
💇🏼 person getting haircut: medium-light skin tone
💇🏽 person getting haircut: medium skin tone
💇🏾 person getting haircut: medium-dark skin tone
💇🏿 person getting haircut: dark skin tone
💇‍♂️ man getting haircut
💇🏻‍♂️ man getting haircut: light skin tone
💇🏼‍♂️ man getting haircut: medium-light skin tone
💇🏽‍♂️ man getting haircut: medium skin tone
💇🏾‍♂️ man getting haircut: medium-dark skin tone
💇🏿‍♂️ man getting haircut: dark skin tone
💇‍♀️ woman getting haircut
💇🏻‍♀️ woman getting haircut: light skin tone
💇🏼‍♀️ woman getting haircut: medium-light skin tone
💇🏽‍♀️ woman getting haircut: medium skin tone
💇🏾‍♀️ woman getting haircut: medium-dark skin tone
💇🏿‍♀️ woman getting haircut: dark skin tone
🚶 person walking
🚶🏻 person walking: light skin tone
🚶🏼 person walking: medium-light skin tone
🚶🏽 person walking: medium skin tone
🚶🏾 person walking: medium-dark skin tone
🚶🏿 person walking: dark skin tone
🚶‍♂️ man walking
🚶🏻‍♂️ man walking: light skin tone
🚶🏼‍♂️ man walking: medium-light skin tone
🚶🏽‍♂️ man walking: medium skin tone
🚶🏾‍♂️ man walking: medium-dark skin tone
🚶🏿‍♂️ man walking: dark skin tone
🚶‍♀️ woman walking
🚶🏻‍♀️ woman walking: light skin tone
🚶🏼‍♀️ woman walking: medium-light skin tone
🚶🏽‍♀️ woman walking: medium skin tone
🚶🏾‍♀️ woman walking: medium-dark skin tone
🚶🏿‍♀️ woman walking: dark skin tone
🏃 person running
🏃🏻 person running: light skin tone
🏃🏼 person running: medium-light skin tone
🏃🏽 person running: medium skin tone
🏃🏾 person running: medium-dark skin tone
🏃🏿 person running: dark skin tone
🏃‍♂️ man running
🏃🏻‍♂️ man running: light skin tone
🏃🏼‍♂️ man running: medium-light skin tone
🏃🏽‍♂️ man running: medium skin tone
🏃🏾‍♂️ man running: medium-dark skin tone
🏃🏿‍♂️ man running: dark skin tone
🏃‍♀️ woman running
🏃🏻‍♀️ woman running: light skin tone
🏃🏼‍♀️ woman running: medium-light skin tone
🏃🏽‍♀️ woman running: medium skin tone
🏃🏾‍♀️ woman running: medium-dark skin tone
🏃🏿‍♀️ woman running: dark skin tone
💃 woman dancing
💃🏻 woman dancing: light skin tone
💃🏼 woman dancing: medium-light skin tone
💃🏽 woman dancing: medium skin tone
💃🏾 woman dancing: medium-dark skin tone
💃🏿 woman dancing: dark skin tone
🕺 man dancing
🕺🏻 man dancing: light skin tone
🕺🏼 man dancing: medium-light skin tone
🕺🏽 man dancing: medium skin tone
🕺🏾 man dancing: medium-dark skin tone
🕺🏿 man dancing: dark skin tone
👯 people with bunny ears
👯‍♂️ men with bunny ears
👯‍♀️ women with bunny ears
🧖 ⊛ person in steamy room
🧖🏻 ⊛ person in steamy room: light skin tone
🧖🏼 ⊛ person in steamy room: medium-light skin tone
🧖🏽 ⊛ person in steamy room: medium skin tone
🧖🏾 ⊛ person in steamy room: medium-dark skin tone
🧖🏿 ⊛ person in steamy room: dark skin tone
🧖‍♀️ ⊛ woman in steamy room
🧖🏻‍♀️ ⊛ woman in steamy room: light skin tone
🧖🏼‍♀️ ⊛ woman in steamy room: medium-light skin tone
🧖🏽‍♀️ ⊛ woman in steamy room: medium skin tone
🧖🏾‍♀️ ⊛ woman in steamy room: medium-dark skin tone
🧖🏿‍♀️ ⊛ woman in steamy room: dark skin tone
🧖‍♂️ ⊛ man in steamy room
🧖🏻‍♂️ ⊛ man in steamy room: light skin tone
🧖🏼‍♂️ ⊛ man in steamy room: medium-light skin tone
🧖🏽‍♂️ ⊛ man in steamy room: medium skin tone
🧖🏾‍♂️ ⊛ man in steamy room: medium-dark skin tone
🧖🏿‍♂️ ⊛ man in steamy room: dark skin tone
🧗 ⊛ person climbing
🧗🏻 ⊛ person climbing: light skin tone
🧗🏼 ⊛ person climbing: medium-light skin tone
🧗🏽 ⊛ person climbing: medium skin tone
🧗🏾 ⊛ person climbing: medium-dark skin tone
🧗🏿 ⊛ person climbing: dark skin tone
🧗‍♀️ ⊛ woman climbing
🧗🏻‍♀️ ⊛ woman climbing: light skin tone
🧗🏼‍♀️ ⊛ woman climbing: medium-light skin tone
🧗🏽‍♀️ ⊛ woman climbing: medium skin tone
🧗🏾‍♀️ ⊛ woman climbing: medium-dark skin tone
🧗🏿‍♀️ ⊛ woman climbing: dark skin tone
🧗‍♂️ ⊛ man climbing
🧗🏻‍♂️ ⊛ man climbing: light skin tone
🧗🏼‍♂️ ⊛ man climbing: medium-light skin tone
🧗🏽‍♂️ ⊛ man climbing: medium skin tone
🧗🏾‍♂️ ⊛ man climbing: medium-dark skin tone
🧗🏿‍♂️ ⊛ man climbing: dark skin tone
🧘 ⊛ person in lotus position
🧘🏻 ⊛ person in lotus position: light skin tone
🧘🏼 ⊛ person in lotus position: medium-light skin tone
🧘🏽 ⊛ person in lotus position: medium skin tone
🧘🏾 ⊛ person in lotus position: medium-dark skin tone
🧘🏿 ⊛ person in lotus position: dark skin tone
🧘‍♀️ ⊛ woman in lotus position
🧘🏻‍♀️ ⊛ woman in lotus position: light skin tone
🧘🏼‍♀️ ⊛ woman in lotus position: medium-light skin tone
🧘🏽‍♀️ ⊛ woman in lotus position: medium skin tone
🧘🏾‍♀️ ⊛ woman in lotus position: medium-dark skin tone
🧘🏿‍♀️ ⊛ woman in lotus position: dark skin tone
🧘‍♂️ ⊛ man in lotus position
🧘🏻‍♂️ ⊛ man in lotus position: light skin tone
🧘🏼‍♂️ ⊛ man in lotus position: medium-light skin tone
🧘🏽‍♂️ ⊛ man in lotus position: medium skin tone
🧘🏾‍♂️ ⊛ man in lotus position: medium-dark skin tone
🧘🏿‍♂️ ⊛ man in lotus position: dark skin tone
🛀 person taking bath
🛀🏻 person taking bath: light skin tone
🛀🏼 person taking bath: medium-light skin tone
🛀🏽 person taking bath: medium skin tone
🛀🏾 person taking bath: medium-dark skin tone
🛀🏿 person taking bath: dark skin tone
🛌 person in bed
🛌🏻 person in bed: light skin tone
🛌🏼 person in bed: medium-light skin tone
🛌🏽 person in bed: medium skin tone
🛌🏾 person in bed: medium-dark skin tone
🛌🏿 person in bed: dark skin tone
🕴 man in suit levitating
🕴🏻 man in suit levitating: light skin tone
🕴🏼 man in suit levitating: medium-light skin tone
🕴🏽 man in suit levitating: medium skin tone
🕴🏾 man in suit levitating: medium-dark skin tone
🕴🏿 man in suit levitating: dark skin tone
🗣 speaking head
👤 bust in silhouette
👥 busts in silhouette
🤺 person fencing
🏇 horse racing
🏇🏻 horse racing: light skin tone
🏇🏼 horse racing: medium-light skin tone
🏇🏽 horse racing: medium skin tone
🏇🏾 horse racing: medium-dark skin tone
🏇🏿 horse racing: dark skin tone
⛷ skier
🏂 snowboarder
🏂🏻 snowboarder: light skin tone
🏂🏼 snowboarder: medium-light skin tone
🏂🏽 snowboarder: medium skin tone
🏂🏾 snowboarder: medium-dark skin tone
🏂🏿 snowboarder: dark skin tone
🏌 person golfing
🏌🏻 person golfing: light skin tone
🏌🏼 person golfing: medium-light skin tone
🏌🏽 person golfing: medium skin tone
🏌🏾 person golfing: medium-dark skin tone
🏌🏿 person golfing: dark skin tone
🏌️‍♂️ man golfing
🏌🏻‍♂️ man golfing: light skin tone
🏌🏼‍♂️ man golfing: medium-light skin tone
🏌🏽‍♂️ man golfing: medium skin tone
🏌🏾‍♂️ man golfing: medium-dark skin tone
🏌🏿‍♂️ man golfing: dark skin tone
🏌️‍♀️ woman golfing
🏌🏻‍♀️ woman golfing: light skin tone
🏌🏼‍♀️ woman golfing: medium-light skin tone
🏌🏽‍♀️ woman golfing: medium skin tone
🏌🏾‍♀️ woman golfing: medium-dark skin tone
🏌🏿‍♀️ woman golfing: dark skin tone
🏄 person surfing
🏄🏻 person surfing: light skin tone
🏄🏼 person surfing: medium-light skin tone
🏄🏽 person surfing: medium skin tone
🏄🏾 person surfing: medium-dark skin tone
🏄🏿 person surfing: dark skin tone
🏄‍♂️ man surfing
🏄🏻‍♂️ man surfing: light skin tone
🏄🏼‍♂️ man surfing: medium-light skin tone
🏄🏽‍♂️ man surfing: medium skin tone
🏄🏾‍♂️ man surfing: medium-dark skin tone
🏄🏿‍♂️ man surfing: dark skin tone
🏄‍♀️ woman surfing
🏄🏻‍♀️ woman surfing: light skin tone
🏄🏼‍♀️ woman surfing: medium-light skin tone
🏄🏽‍♀️ woman surfing: medium skin tone
🏄🏾‍♀️ woman surfing: medium-dark skin tone
🏄🏿‍♀️ woman surfing: dark skin tone
🚣 person rowing boat
🚣🏻 person rowing boat: light skin tone
🚣🏼 person rowing boat: medium-light skin tone
🚣🏽 person rowing boat: medium skin tone
🚣🏾 person rowing boat: medium-dark skin tone
🚣🏿 person rowing boat: dark skin tone
🚣‍♂️ man rowing boat
🚣🏻‍♂️ man rowing boat: light skin tone
🚣🏼‍♂️ man rowing boat: medium-light skin tone
🚣🏽‍♂️ man rowing boat: medium skin tone
🚣🏾‍♂️ man rowing boat: medium-dark skin tone
🚣🏿‍♂️ man rowing boat: dark skin tone
🚣‍♀️ woman rowing boat
🚣🏻‍♀️ woman rowing boat: light skin tone
🚣🏼‍♀️ woman rowing boat: medium-light skin tone
🚣🏽‍♀️ woman rowing boat: medium skin tone
🚣🏾‍♀️ woman rowing boat: medium-dark skin tone
🚣🏿‍♀️ woman rowing boat: dark skin tone
🏊 person swimming
🏊🏻 person swimming: light skin tone
🏊🏼 person swimming: medium-light skin tone
🏊🏽 person swimming: medium skin tone
🏊🏾 person swimming: medium-dark skin tone
🏊🏿 person swimming: dark skin tone
🏊‍♂️ man swimming
🏊🏻‍♂️ man swimming: light skin tone
🏊🏼‍♂️ man swimming: medium-light skin tone
🏊🏽‍♂️ man swimming: medium skin tone
🏊🏾‍♂️ man swimming: medium-dark skin tone
🏊🏿‍♂️ man swimming: dark skin tone
🏊‍♀️ woman swimming
🏊🏻‍♀️ woman swimming: light skin tone
🏊🏼‍♀️ woman swimming: medium-light skin tone
🏊🏽‍♀️ woman swimming: medium skin tone
🏊🏾‍♀️ woman swimming: medium-dark skin tone
🏊🏿‍♀️ woman swimming: dark skin tone
⛹ person bouncing ball
⛹🏻 person bouncing ball: light skin tone
⛹🏼 person bouncing ball: medium-light skin tone
⛹🏽 person bouncing ball: medium skin tone
⛹🏾 person bouncing ball: medium-dark skin tone
⛹🏿 person bouncing ball: dark skin tone
⛹️‍♂️ man bouncing ball
⛹🏻‍♂️ man bouncing ball: light skin tone
⛹🏼‍♂️ man bouncing ball: medium-light skin tone
⛹🏽‍♂️ man bouncing ball: medium skin tone
⛹🏾‍♂️ man bouncing ball: medium-dark skin tone
⛹🏿‍♂️ man bouncing ball: dark skin tone
⛹️‍♀️ woman bouncing ball
⛹🏻‍♀️ woman bouncing ball: light skin tone
⛹🏼‍♀️ woman bouncing ball: medium-light skin tone
⛹🏽‍♀️ woman bouncing ball: medium skin tone
⛹🏾‍♀️ woman bouncing ball: medium-dark skin tone
⛹🏿‍♀️ woman bouncing ball: dark skin tone
🏋 person lifting weights
🏋🏻 person lifting weights: light skin tone
🏋🏼 person lifting weights: medium-light skin tone
🏋🏽 person lifting weights: medium skin tone
🏋🏾 person lifting weights: medium-dark skin tone
🏋🏿 person lifting weights: dark skin tone
🏋️‍♂️ man lifting weights
🏋🏻‍♂️ man lifting weights: light skin tone
🏋🏼‍♂️ man lifting weights: medium-light skin tone
🏋🏽‍♂️ man lifting weights: medium skin tone
🏋🏾‍♂️ man lifting weights: medium-dark skin tone
🏋🏿‍♂️ man lifting weights: dark skin tone
🏋️‍♀️ woman lifting weights
🏋🏻‍♀️ woman lifting weights: light skin tone
🏋🏼‍♀️ woman lifting weights: medium-light skin tone
🏋🏽‍♀️ woman lifting weights: medium skin tone
🏋🏾‍♀️ woman lifting weights: medium-dark skin tone
🏋🏿‍♀️ woman lifting weights: dark skin tone
🚴 person biking
🚴🏻 person biking: light skin tone
🚴🏼 person biking: medium-light skin tone
🚴🏽 person biking: medium skin tone
🚴🏾 person biking: medium-dark skin tone
🚴🏿 person biking: dark skin tone
🚴‍♂️ man biking
🚴🏻‍♂️ man biking: light skin tone
🚴🏼‍♂️ man biking: medium-light skin tone
🚴🏽‍♂️ man biking: medium skin tone
🚴🏾‍♂️ man biking: medium-dark skin tone
🚴🏿‍♂️ man biking: dark skin tone
🚴‍♀️ woman biking
🚴🏻‍♀️ woman biking: light skin tone
🚴🏼‍♀️ woman biking: medium-light skin tone
🚴🏽‍♀️ woman biking: medium skin tone
🚴🏾‍♀️ woman biking: medium-dark skin tone
🚴🏿‍♀️ woman biking: dark skin tone
🚵 person mountain biking
🚵🏻 person mountain biking: light skin tone
🚵🏼 person mountain biking: medium-light skin tone
🚵🏽 person mountain biking: medium skin tone
🚵🏾 person mountain biking: medium-dark skin tone
🚵🏿 person mountain biking: dark skin tone
🚵‍♂️ man mountain biking
🚵🏻‍♂️ man mountain biking: light skin tone
🚵🏼‍♂️ man mountain biking: medium-light skin tone
🚵🏽‍♂️ man mountain biking: medium skin tone
🚵🏾‍♂️ man mountain biking: medium-dark skin tone
🚵🏿‍♂️ man mountain biking: dark skin tone
🚵‍♀️ woman mountain biking
🚵🏻‍♀️ woman mountain biking: light skin tone
🚵🏼‍♀️ woman mountain biking: medium-light skin tone
🚵🏽‍♀️ woman mountain biking: medium skin tone
🚵🏾‍♀️ woman mountain biking: medium-dark skin tone
🚵🏿‍♀️ woman mountain biking: dark skin tone
🏎 racing car
🏍 motorcycle
🤸 person cartwheeling
🤸🏻 person cartwheeling: light skin tone
🤸🏼 person cartwheeling: medium-light skin tone
🤸🏽 person cartwheeling: medium skin tone
🤸🏾 person cartwheeling: medium-dark skin tone
🤸🏿 person cartwheeling: dark skin tone
🤸‍♂️ man cartwheeling
🤸🏻‍♂️ man cartwheeling: light skin tone
🤸🏼‍♂️ man cartwheeling: medium-light skin tone
🤸🏽‍♂️ man cartwheeling: medium skin tone
🤸🏾‍♂️ man cartwheeling: medium-dark skin tone
🤸🏿‍♂️ man cartwheeling: dark skin tone
🤸‍♀️ woman cartwheeling
🤸🏻‍♀️ woman cartwheeling: light skin tone
🤸🏼‍♀️ woman cartwheeling: medium-light skin tone
🤸🏽‍♀️ woman cartwheeling: medium skin tone
🤸🏾‍♀️ woman cartwheeling: medium-dark skin tone
🤸🏿‍♀️ woman cartwheeling: dark skin tone
🤼 people wrestling
🤼‍♂️ men wrestling
🤼‍♀️ women wrestling
🤽 person playing water polo
🤽🏻 person playing water polo: light skin tone
🤽🏼 person playing water polo: medium-light skin tone
🤽🏽 person playing water polo: medium skin tone
🤽🏾 person playing water polo: medium-dark skin tone
🤽🏿 person playing water polo: dark skin tone
🤽‍♂️ man playing water polo
🤽🏻‍♂️ man playing water polo: light skin tone
🤽🏼‍♂️ man playing water polo: medium-light skin tone
🤽🏽‍♂️ man playing water polo: medium skin tone
🤽🏾‍♂️ man playing water polo: medium-dark skin tone
🤽🏿‍♂️ man playing water polo: dark skin tone
🤽‍♀️ woman playing water polo
🤽🏻‍♀️ woman playing water polo: light skin tone
🤽🏼‍♀️ woman playing water polo: medium-light skin tone
🤽🏽‍♀️ woman playing water polo: medium skin tone
🤽🏾‍♀️ woman playing water polo: medium-dark skin tone
🤽🏿‍♀️ woman playing water polo: dark skin tone
🤾 person playing handball
🤾🏻 person playing handball: light skin tone
🤾🏼 person playing handball: medium-light skin tone
🤾🏽 person playing handball: medium skin tone
🤾🏾 person playing handball: medium-dark skin tone
🤾🏿 person playing handball: dark skin tone
🤾‍♂️ man playing handball
🤾🏻‍♂️ man playing handball: light skin tone
🤾🏼‍♂️ man playing handball: medium-light skin tone
🤾🏽‍♂️ man playing handball: medium skin tone
🤾🏾‍♂️ man playing handball: medium-dark skin tone
🤾🏿‍♂️ man playing handball: dark skin tone
🤾‍♀️ woman playing handball
🤾🏻‍♀️ woman playing handball: light skin tone
🤾🏼‍♀️ woman playing handball: medium-light skin tone
🤾🏽‍♀️ woman playing handball: medium skin tone
🤾🏾‍♀️ woman playing handball: medium-dark skin tone
🤾🏿‍♀️ woman playing handball: dark skin tone
🤹 person juggling
🤹🏻 person juggling: light skin tone
🤹🏼 person juggling: medium-light skin tone
🤹🏽 person juggling: medium skin tone
🤹🏾 person juggling: medium-dark skin tone
🤹🏿 person juggling: dark skin tone
🤹‍♂️ man juggling
🤹🏻‍♂️ man juggling: light skin tone
🤹🏼‍♂️ man juggling: medium-light skin tone
🤹🏽‍♂️ man juggling: medium skin tone
🤹🏾‍♂️ man juggling: medium-dark skin tone
🤹🏿‍♂️ man juggling: dark skin tone
🤹‍♀️ woman juggling
🤹🏻‍♀️ woman juggling: light skin tone
🤹🏼‍♀️ woman juggling: medium-light skin tone
🤹🏽‍♀️ woman juggling: medium skin tone
🤹🏾‍♀️ woman juggling: medium-dark skin tone
🤹🏿‍♀️ woman juggling: dark skin tone
👫 man and woman holding hands
👬 two men holding hands
👭 two women holding hands
💏 kiss
👩‍❤️‍💋‍👨 kiss: woman, man
👨‍❤️‍💋‍👨 kiss: man, man
👩‍❤️‍💋‍👩 kiss: woman, woman
💑 couple with heart
👩‍❤️‍👨 couple with heart: woman, man
👨‍❤️‍👨 couple with heart: man, man
👩‍❤️‍👩 couple with heart: woman, woman
👪 family
👨‍👩‍👦 family: man, woman, boy
👨‍👩‍👧 family: man, woman, girl
👨‍👩‍👧‍👦 family: man, woman, girl, boy
👨‍👩‍👦‍👦 family: man, woman, boy, boy
👨‍👩‍👧‍👧 family: man, woman, girl, girl
👨‍👨‍👦 family: man, man, boy
👨‍👨‍👧 family: man, man, girl
👨‍👨‍👧‍👦 family: man, man, girl, boy
👨‍👨‍👦‍👦 family: man, man, boy, boy
👨‍👨‍👧‍👧 family: man, man, girl, girl
👩‍👩‍👦 family: woman, woman, boy
👩‍👩‍👧 family: woman, woman, girl
👩‍👩‍👧‍👦 family: woman, woman, girl, boy
👩‍👩‍👦‍👦 family: woman, woman, boy, boy
👩‍👩‍👧‍👧 family: woman, woman, girl, girl
👨‍👦 family: man, boy
👨‍👦‍👦 family: man, boy, boy
👨‍👧 family: man, girl
👨‍👧‍👦 family: man, girl, boy
👨‍👧‍👧 family: man, girl, girl
👩‍👦 family: woman, boy
👩‍👦‍👦 family: woman, boy, boy
👩‍👧 family: woman, girl
👩‍👧‍👦 family: woman, girl, boy
👩‍👧‍👧 family: woman, girl, girl
🤳 selfie
🤳🏻 selfie: light skin tone
🤳🏼 selfie: medium-light skin tone
🤳🏽 selfie: medium skin tone
🤳🏾 selfie: medium-dark skin tone
🤳🏿 selfie: dark skin tone
💪 flexed biceps
💪🏻 flexed biceps: light skin tone
💪🏼 flexed biceps: medium-light skin tone
💪🏽 flexed biceps: medium skin tone
💪🏾 flexed biceps: medium-dark skin tone
💪🏿 flexed biceps: dark skin tone
👈 backhand index pointing left
👈🏻 backhand index pointing left: light skin tone
👈🏼 backhand index pointing left: medium-light skin tone
👈🏽 backhand index pointing left: medium skin tone
👈🏾 backhand index pointing left: medium-dark skin tone
👈🏿 backhand index pointing left: dark skin tone
👉 backhand index pointing right
👉🏻 backhand index pointing right: light skin tone
👉🏼 backhand index pointing right: medium-light skin tone
👉🏽 backhand index pointing right: medium skin tone
👉🏾 backhand index pointing right: medium-dark skin tone
👉🏿 backhand index pointing right: dark skin tone
☝ index pointing up
☝🏻 index pointing up: light skin tone
☝🏼 index pointing up: medium-light skin tone
☝🏽 index pointing up: medium skin tone
☝🏾 index pointing up: medium-dark skin tone
☝🏿 index pointing up: dark skin tone
👆 backhand index pointing up
👆🏻 backhand index pointing up: light skin tone
👆🏼 backhand index pointing up: medium-light skin tone
👆🏽 backhand index pointing up: medium skin tone
👆🏾 backhand index pointing up: medium-dark skin tone
👆🏿 backhand index pointing up: dark skin tone
🖕 middle finger
🖕🏻 middle finger: light skin tone
🖕🏼 middle finger: medium-light skin tone
🖕🏽 middle finger: medium skin tone
🖕🏾 middle finger: medium-dark skin tone
🖕🏿 middle finger: dark skin tone
👇 backhand index pointing down
👇🏻 backhand index pointing down: light skin tone
👇🏼 backhand index pointing down: medium-light skin tone
👇🏽 backhand index pointing down: medium skin tone
👇🏾 backhand index pointing down: medium-dark skin tone
👇🏿 backhand index pointing down: dark skin tone
✌ victory hand
✌🏻 victory hand: light skin tone
✌🏼 victory hand: medium-light skin tone
✌🏽 victory hand: medium skin tone
✌🏾 victory hand: medium-dark skin tone
✌🏿 victory hand: dark skin tone
🤞 crossed fingers
🤞🏻 crossed fingers: light skin tone
🤞🏼 crossed fingers: medium-light skin tone
🤞🏽 crossed fingers: medium skin tone
🤞🏾 crossed fingers: medium-dark skin tone
🤞🏿 crossed fingers: dark skin tone
🖖 vulcan salute
🖖🏻 vulcan salute: light skin tone
🖖🏼 vulcan salute: medium-light skin tone
🖖🏽 vulcan salute: medium skin tone
🖖🏾 vulcan salute: medium-dark skin tone
🖖🏿 vulcan salute: dark skin tone
🤘 sign of the horns
🤘🏻 sign of the horns: light skin tone
🤘🏼 sign of the horns: medium-light skin tone
🤘🏽 sign of the horns: medium skin tone
🤘🏾 sign of the horns: medium-dark skin tone
🤘🏿 sign of the horns: dark skin tone
🤙 call me hand
🤙🏻 call me hand: light skin tone
🤙🏼 call me hand: medium-light skin tone
🤙🏽 call me hand: medium skin tone
🤙🏾 call me hand: medium-dark skin tone
🤙🏿 call me hand: dark skin tone
🖐 hand with fingers splayed
🖐🏻 hand with fingers splayed: light skin tone
🖐🏼 hand with fingers splayed: medium-light skin tone
🖐🏽 hand with fingers splayed: medium skin tone
🖐🏾 hand with fingers splayed: medium-dark skin tone
🖐🏿 hand with fingers splayed: dark skin tone
✋ raised hand
✋🏻 raised hand: light skin tone
✋🏼 raised hand: medium-light skin tone
✋🏽 raised hand: medium skin tone
✋🏾 raised hand: medium-dark skin tone
✋🏿 raised hand: dark skin tone
👌 OK hand
👌🏻 OK hand: light skin tone
👌🏼 OK hand: medium-light skin tone
👌🏽 OK hand: medium skin tone
👌🏾 OK hand: medium-dark skin tone
👌🏿 OK hand: dark skin tone
👍 thumbs up
👍🏻 thumbs up: light skin tone
👍🏼 thumbs up: medium-light skin tone
👍🏽 thumbs up: medium skin tone
👍🏾 thumbs up: medium-dark skin tone
👍🏿 thumbs up: dark skin tone
👎 thumbs down
👎🏻 thumbs down: light skin tone
👎🏼 thumbs down: medium-light skin tone
👎🏽 thumbs down: medium skin tone
👎🏾 thumbs down: medium-dark skin tone
👎🏿 thumbs down: dark skin tone
✊ raised fist
✊🏻 raised fist: light skin tone
✊🏼 raised fist: medium-light skin tone
✊🏽 raised fist: medium skin tone
✊🏾 raised fist: medium-dark skin tone
✊🏿 raised fist: dark skin tone
👊 oncoming fist
👊🏻 oncoming fist: light skin tone
👊🏼 oncoming fist: medium-light skin tone
👊🏽 oncoming fist: medium skin tone
👊🏾 oncoming fist: medium-dark skin tone
👊🏿 oncoming fist: dark skin tone
🤛 left-facing fist
🤛🏻 left-facing fist: light skin tone
🤛🏼 left-facing fist: medium-light skin tone
🤛🏽 left-facing fist: medium skin tone
🤛🏾 left-facing fist: medium-dark skin tone
🤛🏿 left-facing fist: dark skin tone
🤜 right-facing fist
🤜🏻 right-facing fist: light skin tone
🤜🏼 right-facing fist: medium-light skin tone
🤜🏽 right-facing fist: medium skin tone
🤜🏾 right-facing fist: medium-dark skin tone
🤜🏿 right-facing fist: dark skin tone
🤚 raised back of hand
🤚🏻 raised back of hand: light skin tone
🤚🏼 raised back of hand: medium-light skin tone
🤚🏽 raised back of hand: medium skin tone
🤚🏾 raised back of hand: medium-dark skin tone
🤚🏿 raised back of hand: dark skin tone
👋 waving hand
👋🏻 waving hand: light skin tone
👋🏼 waving hand: medium-light skin tone
👋🏽 waving hand: medium skin tone
👋🏾 waving hand: medium-dark skin tone
👋🏿 waving hand: dark skin tone
🤟 ⊛ love-you gesture
🤟🏻 ⊛ love-you gesture: light skin tone
🤟🏼 ⊛ love-you gesture: medium-light skin tone
🤟🏽 ⊛ love-you gesture: medium skin tone
🤟🏾 ⊛ love-you gesture: medium-dark skin tone
🤟🏿 ⊛ love-you gesture: dark skin tone
✍ writing hand
✍🏻 writing hand: light skin tone
✍🏼 writing hand: medium-light skin tone
✍🏽 writing hand: medium skin tone
✍🏾 writing hand: medium-dark skin tone
✍🏿 writing hand: dark skin tone
👏 clapping hands
👏🏻 clapping hands: light skin tone
👏🏼 clapping hands: medium-light skin tone
👏🏽 clapping hands: medium skin tone
👏🏾 clapping hands: medium-dark skin tone
👏🏿 clapping hands: dark skin tone
👐 open hands
👐🏻 open hands: light skin tone
👐🏼 open hands: medium-light skin tone
👐🏽 open hands: medium skin tone
👐🏾 open hands: medium-dark skin tone
👐🏿 open hands: dark skin tone
🙌 raising hands
🙌🏻 raising hands: light skin tone
🙌🏼 raising hands: medium-light skin tone
🙌🏽 raising hands: medium skin tone
🙌🏾 raising hands: medium-dark skin tone
🙌🏿 raising hands: dark skin tone
🤲 ⊛ palms up together
🤲🏻 ⊛ palms up together: light skin tone
🤲🏼 ⊛ palms up together: medium-light skin tone
🤲🏽 ⊛ palms up together: medium skin tone
🤲🏾 ⊛ palms up together: medium-dark skin tone
🤲🏿 ⊛ palms up together: dark skin tone
🙏 folded hands
🙏🏻 folded hands: light skin tone
🙏🏼 folded hands: medium-light skin tone
🙏🏽 folded hands: medium skin tone
🙏🏾 folded hands: medium-dark skin tone
🙏🏿 folded hands: dark skin tone
🤝 handshake
💅 nail polish
💅🏻 nail polish: light skin tone
💅🏼 nail polish: medium-light skin tone
💅🏽 nail polish: medium skin tone
💅🏾 nail polish: medium-dark skin tone
💅🏿 nail polish: dark skin tone
👂 ear
👂🏻 ear: light skin tone
👂🏼 ear: medium-light skin tone
👂🏽 ear: medium skin tone
👂🏾 ear: medium-dark skin tone
👂🏿 ear: dark skin tone
👃 nose
👃🏻 nose: light skin tone
👃🏼 nose: medium-light skin tone
👃🏽 nose: medium skin tone
👃🏾 nose: medium-dark skin tone
👃🏿 nose: dark skin tone
👣 footprints
👀 eyes
👁 eye
👁️‍🗨️ eye in speech bubble
🧠 ⊛ brain
👅 tongue
👄 mouth
💋 kiss mark
💘 heart with arrow
❤ red heart
💓 beating heart
💔 broken heart
💕 two hearts
💖 sparkling heart
💗 growing heart
💙 blue heart
💚 green heart
💛 yellow heart
🧡 ⊛ orange heart
💜 purple heart
🖤 black heart
💝 heart with ribbon
💞 revolving hearts
💟 heart decoration
❣ heavy heart exclamation
💌 love letter
💤 zzz
💢 anger symbol
💣 bomb
💥 collision
💦 sweat droplets
💨 dashing away
💫 dizzy
💬 speech balloon
🗨 left speech bubble
🗯 right anger bubble
💭 thought balloon
🕳 hole
👓 glasses
🕶 sunglasses
👔 necktie
👕 t-shirt
👖 jeans
🧣 ⊛ scarf
🧤 ⊛ gloves
🧥 ⊛ coat
🧦 ⊛ socks
👗 dress
👘 kimono
👙 bikini
👚 woman’s clothes
👛 purse
👜 handbag
👝 clutch bag
🛍 shopping bags
🎒 school backpack
👞 man’s shoe
👟 running shoe
👠 high-heeled shoe
👡 woman’s sandal
👢 woman’s boot
👑 crown
👒 woman’s hat
🎩 top hat
🎓 graduation cap
🧢 ⊛ billed cap
⛑ rescue worker’s helmet
📿 prayer beads
💄 lipstick
💍 ring
💎 gem stone
🐵 monkey face
🐒 monkey
🦍 gorilla
🐶 dog face
🐕 dog
🐩 poodle
🐺 wolf face
🦊 fox face
🐱 cat face
🐈 cat
🦁 lion face
🐯 tiger face
🐅 tiger
🐆 leopard
🐴 horse face
🐎 horse
🦄 unicorn face
🦓 ⊛ zebra
🦌 deer
🐮 cow face
🐂 ox
🐃 water buffalo
🐄 cow
🐷 pig face
🐖 pig
🐗 boar
🐽 pig nose
🐏 ram
🐑 ewe
🐐 goat
🐪 camel
🐫 two-hump camel
🦒 ⊛ giraffe
🐘 elephant
🦏 rhinoceros
🐭 mouse face
🐁 mouse
🐀 rat
🐹 hamster face
🐰 rabbit face
🐇 rabbit
🐿 chipmunk
🦔 ⊛ hedgehog
🦇 bat
🐻 bear face
🐨 koala
🐼 panda face
🐾 paw prints
🦃 turkey
🐔 chicken
🐓 rooster
🐣 hatching chick
🐤 baby chick
🐥 front-facing baby chick
🐦 bird
🐧 penguin
🕊 dove
🦅 eagle
🦆 duck
🦉 owl
🐸 frog face
🐊 crocodile
🐢 turtle
🦎 lizard
🐍 snake
🐲 dragon face
🐉 dragon
🦕 ⊛ sauropod
🦖 ⊛ T-Rex
🐳 spouting whale
🐋 whale
🐬 dolphin
🐟 fish
🐠 tropical fish
🐡 blowfish
🦈 shark
🐙 octopus
🐚 spiral shell
🦀 crab
🦐 shrimp
🦑 squid
🐌 snail
🦋 butterfly
🐛 bug
🐜 ant
🐝 honeybee
🐞 lady beetle
🦗 ⊛ cricket
🕷 spider
🕸 spider web
🦂 scorpion
💐 bouquet
🌸 cherry blossom
💮 white flower
🏵 rosette
🌹 rose
🥀 wilted flower
🌺 hibiscus
🌻 sunflower
🌼 blossom
🌷 tulip
🌱 seedling
🌲 evergreen tree
🌳 deciduous tree
🌴 palm tree
🌵 cactus
🌾 sheaf of rice
🌿 herb
☘ shamrock
🍀 four leaf clover
🍁 maple leaf
🍂 fallen leaf
🍃 leaf fluttering in wind
🍇 grapes
🍈 melon
🍉 watermelon
🍊 tangerine
🍋 lemon
🍌 banana
🍍 pineapple
🍎 red apple
🍏 green apple
🍐 pear
🍑 peach
🍒 cherries
🍓 strawberry
🥝 kiwi fruit
🍅 tomato
🥥 ⊛ coconut
🥑 avocado
🍆 eggplant
🥔 potato
🥕 carrot
🌽 ear of corn
🌶 hot pepper
🥒 cucumber
🥦 ⊛ broccoli
🍄 mushroom
🥜 peanuts
🌰 chestnut
🍞 bread
🥐 croissant
🥖 baguette bread
🥨 ⊛ pretzel
🥞 pancakes
🧀 cheese wedge
🍖 meat on bone
🍗 poultry leg
🥩 ⊛ cut of meat
🥓 bacon
🍔 hamburger
🍟 french fries
🍕 pizza
🌭 hot dog
🥪 ⊛ sandwich
🌮 taco
🌯 burrito
🥙 stuffed flatbread
🥚 egg
🍳 cooking
🥘 shallow pan of food
🍲 pot of food
🥣 ⊛ bowl with spoon
🥗 green salad
🍿 popcorn
🥫 ⊛ canned food
🍱 bento box
🍘 rice cracker
🍙 rice ball
🍚 cooked rice
🍛 curry rice
🍜 steaming bowl
🍝 spaghetti
🍠 roasted sweet potato
🍢 oden
🍣 sushi
🍤 fried shrimp
🍥 fish cake with swirl
🍡 dango
🥟 ⊛ dumpling
🥠 ⊛ fortune cookie
🥡 ⊛ takeout box
🍦 soft ice cream
🍧 shaved ice
🍨 ice cream
🍩 doughnut
🍪 cookie
🎂 birthday cake
🍰 shortcake
🥧 ⊛ pie
🍫 chocolate bar
🍬 candy
🍭 lollipop
🍮 custard
🍯 honey pot
🍼 baby bottle
🥛 glass of milk
☕ hot beverage
🍵 teacup without handle
🍶 sake
🍾 bottle with popping cork
🍷 wine glass
🍸 cocktail glass
🍹 tropical drink
🍺 beer mug
🍻 clinking beer mugs
🥂 clinking glasses
🥃 tumbler glass
🥤 ⊛ cup with straw
🥢 ⊛ chopsticks
🍽 fork and knife with plate
🍴 fork and knife
🥄 spoon
🔪 kitchen knife
🏺 amphora
🌍 globe showing Europe-Africa
🌎 globe showing Americas
🌏 globe showing Asia-Australia
🌐 globe with meridians
🗺 world map
🗾 map of Japan
🏔 snow-capped mountain
⛰ mountain
🌋 volcano
🗻 mount fuji
🏕 camping
🏖 beach with umbrella
🏜 desert
🏝 desert island
🏞 national park
🏟 stadium
🏛 classical building
🏗 building construction
🏘 houses
🏙 cityscape
🏚 derelict house
🏠 house
🏡 house with garden
🏢 office building
🏣 Japanese post office
🏤 post office
🏥 hospital
🏦 bank
🏨 hotel
🏩 love hotel
🏪 convenience store
🏫 school
🏬 department store
🏭 factory
🏯 Japanese castle
🏰 castle
💒 wedding
🗼 Tokyo tower
🗽 Statue of Liberty
⛪ church
🕌 mosque
🕍 synagogue
⛩ shinto shrine
🕋 kaaba
⛲ fountain
⛺ tent
🌁 foggy
🌃 night with stars
🌄 sunrise over mountains
🌅 sunrise
🌆 cityscape at dusk
🌇 sunset
🌉 bridge at night
♨ hot springs
🌌 milky way
🎠 carousel horse
🎡 ferris wheel
🎢 roller coaster
💈 barber pole
🎪 circus tent
🎭 performing arts
🖼 framed picture
🎨 artist palette
🎰 slot machine
🚂 locomotive
🚃 railway car
🚄 high-speed train
🚅 bullet train
🚆 train
🚇 metro
🚈 light rail
🚉 station
🚊 tram
🚝 monorail
🚞 mountain railway
🚋 tram car
🚌 bus
🚍 oncoming bus
🚎 trolleybus
🚐 minibus
🚑 ambulance
🚒 fire engine
🚓 police car
🚔 oncoming police car
🚕 taxi
🚖 oncoming taxi
🚗 automobile
🚘 oncoming automobile
🚙 sport utility vehicle
🚚 delivery truck
🚛 articulated lorry
🚜 tractor
🚲 bicycle
🛴 kick scooter
🛵 motor scooter
🚏 bus stop
🛣 motorway
🛤 railway track
⛽ fuel pump
🚨 police car light
🚥 horizontal traffic light
🚦 vertical traffic light
🚧 construction
🛑 stop sign
⚓ anchor
⛵ sailboat
🛶 canoe
🚤 speedboat
🛳 passenger ship
⛴ ferry
🛥 motor boat
🚢 ship
✈ airplane
🛩 small airplane
🛫 airplane departure
🛬 airplane arrival
💺 seat
🚁 helicopter
🚟 suspension railway
🚠 mountain cableway
🚡 aerial tramway
🛰 satellite
🚀 rocket
🛸 ⊛ flying saucer
🛎 bellhop bell
🚪 door
🛏 bed
🛋 couch and lamp
🚽 toilet
🚿 shower
🛁 bathtub
⌛ hourglass done
⏳ hourglass not done
⌚ watch
⏰ alarm clock
⏱ stopwatch
⏲ timer clock
🕰 mantelpiece clock
🕛 twelve o’clock
🕧 twelve-thirty
🕐 one o’clock
🕜 one-thirty
🕑 two o’clock
🕝 two-thirty
🕒 three o’clock
🕞 three-thirty
🕓 four o’clock
🕟 four-thirty
🕔 five o’clock
🕠 five-thirty
🕕 six o’clock
🕡 six-thirty
🕖 seven o’clock
🕢 seven-thirty
🕗 eight o’clock
🕣 eight-thirty
🕘 nine o’clock
🕤 nine-thirty
🕙 ten o’clock
🕥 ten-thirty
🕚 eleven o’clock
🕦 eleven-thirty
🌑 new moon
🌒 waxing crescent moon
🌓 first quarter moon
🌔 waxing gibbous moon
🌕 full moon
🌖 waning gibbous moon
🌗 last quarter moon
🌘 waning crescent moon
🌙 crescent moon
🌚 new moon face
🌛 first quarter moon face
🌜 last quarter moon face
🌡 thermometer
☀ sun
🌝 full moon face
🌞 sun with face
⭐ white medium star
🌟 glowing star
🌠 shooting star
☁ cloud
⛅ sun behind cloud
⛈ cloud with lightning and rain
🌤 sun behind small cloud
🌥 sun behind large cloud
🌦 sun behind rain cloud
🌧 cloud with rain
🌨 cloud with snow
🌩 cloud with lightning
🌪 tornado
🌫 fog
🌬 wind face
🌀 cyclone
🌈 rainbow
🌂 closed umbrella
☂ umbrella
☔ umbrella with rain drops
⛱ umbrella on ground
⚡ high voltage
❄ snowflake
☃ snowman
⛄ snowman without snow
☄ comet
🔥 fire
💧 droplet
🌊 water wave
🎃 jack-o-lantern
🎄 Christmas tree
🎆 fireworks
🎇 sparkler
✨ sparkles
🎈 balloon
🎉 party popper
🎊 confetti ball
🎋 tanabata tree
🎍 pine decoration
🎎 Japanese dolls
🎏 carp streamer
🎐 wind chime
🎑 moon viewing ceremony
🎀 ribbon
🎁 wrapped gift
🎗 reminder ribbon
🎟 admission tickets
🎫 ticket
🎖 military medal
🏆 trophy
🏅 sports medal
🥇 1st place medal
🥈 2nd place medal
🥉 3rd place medal
⚽ soccer ball
⚾ baseball
🏀 basketball
🏐 volleyball
🏈 american football
🏉 rugby football
🎾 tennis
🎱 pool 8 ball
🎳 bowling
🏏 cricket game
🏑 field hockey
🏒 ice hockey
🏓 ping pong
🏸 badminton
🥊 boxing glove
🥋 martial arts uniform
🥅 goal net
🎯 direct hit
⛳ flag in hole
⛸ ice skate
🎣 fishing pole
🎽 running shirt
🎿 skis
🛷 ⊛ sled
🥌 ⊛ curling stone
🎮 video game
🕹 joystick
🎲 game die
♠ spade suit
♥ heart suit
♦ diamond suit
♣ club suit
🃏 joker
🀄 mahjong red dragon
🎴 flower playing cards
🔇 muted speaker
🔈 speaker low volume
🔉 speaker medium volume
🔊 speaker high volume
📢 loudspeaker
📣 megaphone
📯 postal horn
🔔 bell
🔕 bell with slash
🎼 musical score
🎵 musical note
🎶 musical notes
🎙 studio microphone
🎚 level slider
🎛 control knobs
🎤 microphone
🎧 headphone
📻 radio
🎷 saxophone
🎸 guitar
🎹 musical keyboard
🎺 trumpet
🎻 violin
🥁 drum
📱 mobile phone
📲 mobile phone with arrow
☎ telephone
📞 telephone receiver
📟 pager
📠 fax machine
🔋 battery
🔌 electric plug
💻 laptop computer
🖥 desktop computer
🖨 printer
⌨ keyboard
🖱 computer mouse
🖲 trackball
💽 computer disk
💾 floppy disk
💿 optical disk
📀 dvd
🎥 movie camera
🎞 film frames
📽 film projector
🎬 clapper board
📺 television
📷 camera
📸 camera with flash
📹 video camera
📼 videocassette
🔍 magnifying glass tilted left
🔎 magnifying glass tilted right
🔬 microscope
🔭 telescope
📡 satellite antenna
🕯 candle
💡 light bulb
🔦 flashlight
🏮 red paper lantern
📔 notebook with decorative cover
📕 closed book
📖 open book
📗 green book
📘 blue book
📙 orange book
📚 books
📓 notebook
📒 ledger
📃 page with curl
📜 scroll
📄 page facing up
📰 newspaper
🗞 rolled-up newspaper
📑 bookmark tabs
🔖 bookmark
🏷 label
💰 money bag
💴 yen banknote
💵 dollar banknote
💶 euro banknote
💷 pound banknote
💸 money with wings
💳 credit card
💹 chart increasing with yen
💱 currency exchange
💲 heavy dollar sign
✉ envelope
📧 e-mail
📨 incoming envelope
📩 envelope with arrow
📤 outbox tray
📥 inbox tray
📦 package
📫 closed mailbox with raised flag
📪 closed mailbox with lowered flag
📬 open mailbox with raised flag
📭 open mailbox with lowered flag
📮 postbox
🗳 ballot box with ballot
✏ pencil
✒ black nib
🖋 fountain pen
🖊 pen
🖌 paintbrush
🖍 crayon
📝 memo
💼 briefcase
📁 file folder
📂 open file folder
🗂 card index dividers
📅 calendar
📆 tear-off calendar
🗒 spiral notepad
🗓 spiral calendar
📇 card index
📈 chart increasing
📉 chart decreasing
📊 bar chart
📋 clipboard
📌 pushpin
📍 round pushpin
📎 paperclip
🖇 linked paperclips
📏 straight ruler
📐 triangular ruler
✂ scissors
🗃 card file box
🗄 file cabinet
🗑 wastebasket
🔒 locked
🔓 unlocked
🔏 locked with pen
🔐 locked with key
🔑 key
🗝 old key
🔨 hammer
⛏ pick
⚒ hammer and pick
🛠 hammer and wrench
🗡 dagger
⚔ crossed swords
🔫 pistol
🏹 bow and arrow
🛡 shield
🔧 wrench
🔩 nut and bolt
⚙ gear
🗜 clamp
⚗ alembic
⚖ balance scale
🔗 link
⛓ chains
💉 syringe
💊 pill
🚬 cigarette
⚰ coffin
⚱ funeral urn
🗿 moai
🛢 oil drum
🔮 crystal ball
🛒 shopping cart
🏧 ATM sign
🚮 litter in bin sign
🚰 potable water
♿ wheelchair symbol
🚹 men’s room
🚺 women’s room
🚻 restroom
🚼 baby symbol
🚾 water closet
🛂 passport control
🛃 customs
🛄 baggage claim
🛅 left luggage
⚠ warning
🚸 children crossing
⛔ no entry
🚫 prohibited
🚳 no bicycles
🚭 no smoking
🚯 no littering
🚱 non-potable water
🚷 no pedestrians
📵 no mobile phones
🔞 no one under eighteen
☢ radioactive
☣ biohazard
⬆ up arrow
↗ up-right arrow
➡ right arrow
↘ down-right arrow
⬇ down arrow
↙ down-left arrow
⬅ left arrow
↖ up-left arrow
↕ up-down arrow
↔ left-right arrow
↩ right arrow curving left
↪ left arrow curving right
⤴ right arrow curving up
⤵ right arrow curving down
🔃 clockwise vertical arrows
🔄 counterclockwise arrows button
🔙 BACK arrow
🔚 END arrow
🔛 ON! arrow
🔜 SOON arrow
🔝 TOP arrow
🛐 place of worship
⚛ atom symbol
🕉 om
✡ star of David
☸ wheel of dharma
☯ yin yang
✝ latin cross
☦ orthodox cross
☪ star and crescent
☮ peace symbol
🕎 menorah
🔯 dotted six-pointed star
♈ Aries
♉ Taurus
♊ Gemini
♋ Cancer
♌ Leo
♍ Virgo
♎ Libra
♏ Scorpius
♐ Sagittarius
♑ Capricorn
♒ Aquarius
♓ Pisces
⛎ Ophiuchus
🔀 shuffle tracks button
🔁 repeat button
🔂 repeat single button
▶ play button
⏩ fast-forward button
⏭ next track button
⏯ play or pause button
◀ reverse button
⏪ fast reverse button
⏮ last track button
🔼 up button
⏫ fast up button
🔽 down button
⏬ fast down button
⏸ pause button
⏹ stop button
⏺ record button
⏏ eject button
🎦 cinema
🔅 dim button
🔆 bright button
📶 antenna bars
📳 vibration mode
📴 mobile phone off
♀ female sign
♂ male sign
⚕ medical symbol
♻ recycling symbol
⚜ fleur-de-lis
🔱 trident emblem
📛 name badge
🔰 Japanese symbol for beginner
⭕ heavy large circle
✅ white heavy check mark
☑ ballot box with check
✔ heavy check mark
✖ heavy multiplication x
❌ cross mark
❎ cross mark button
➕ heavy plus sign
➖ heavy minus sign
➗ heavy division sign
➰ curly loop
➿ double curly loop
〽 part alternation mark
✳ eight-spoked asterisk
✴ eight-pointed star
❇ sparkle
‼ double exclamation mark
⁉ exclamation question mark
❓ question mark
❔ white question mark
❕ white exclamation mark
❗ exclamation mark
〰 wavy dash
© copyright
® registered
™ trade mark
#️⃣ keycap: #
*️⃣ keycap: *
0️⃣ keycap: 0
1️⃣ keycap: 1
2️⃣ keycap: 2
3️⃣ keycap: 3
4️⃣ keycap: 4
5️⃣ keycap: 5
6️⃣ keycap: 6
7️⃣ keycap: 7
8️⃣ keycap: 8
9️⃣ keycap: 9
🔟 keycap 10
💯 hundred points
🔠 input latin uppercase
🔡 input latin lowercase
🔢 input numbers
🔣 input symbols
🔤 input latin letters
🅰 A button (blood type)
🆎 AB button (blood type)
🅱 B button (blood type)
🆑 CL button
🆒 COOL button
🆓 FREE button
ℹ information
🆔 ID button
Ⓜ circled M
🆕 NEW button
🆖 NG button
🅾 O button (blood type)
🆗 OK button
🅿 P button
🆘 SOS button
🆙 UP! button
🆚 VS button
🈁 Japanese “here” button
🈂 Japanese “service charge” button
🈷 Japanese “monthly amount” button
🈶 Japanese “not free of charge” button
🈯 Japanese “reserved” button
🉐 Japanese “bargain” button
🈹 Japanese “discount” button
🈚 Japanese “free of charge” button
🈲 Japanese “prohibited” button
🉑 Japanese “acceptable” button
🈸 Japanese “application” button
🈴 Japanese “passing grade” button
🈳 Japanese “vacancy” button
㊗ Japanese “congratulations” button
㊙ Japanese “secret” button
🈺 Japanese “open for business” button
🈵 Japanese “no vacancy” button
▪ black small square
▫ white small square
◻ white medium square
◼ black medium square
◽ white medium-small square
◾ black medium-small square
⬛ black large square
⬜ white large square
🔶 large orange diamond
🔷 large blue diamond
🔸 small orange diamond
🔹 small blue diamond
🔺 red triangle pointed up
🔻 red triangle pointed down
💠 diamond with a dot
🔘 radio button
🔲 black square button
🔳 white square button
⚪ white circle
⚫ black circle
🔴 red circle
🔵 blue circle
🏁 chequered flag
🚩 triangular flag
🎌 crossed flags
🏴 black flag
🏳 white flag
🏳️‍🌈 rainbow flag
🇦🇨 Ascension Island
🇦🇩 Andorra
🇦🇪 United Arab Emirates
🇦🇫 Afghanistan
🇦🇬 Antigua &amp; Barbuda
🇦🇮 Anguilla
🇦🇱 Albania
🇦🇲 Armenia
🇦🇴 Angola
🇦🇶 Antarctica
🇦🇷 Argentina
🇦🇸 American Samoa
🇦🇹 Austria
🇦🇺 Australia
🇦🇼 Aruba
🇦🇽 Åland Islands
🇦🇿 Azerbaijan
🇧🇦 Bosnia &amp; Herzegovina
🇧🇧 Barbados
🇧🇩 Bangladesh
🇧🇪 Belgium
🇧🇫 Burkina Faso
🇧🇬 Bulgaria
🇧🇭 Bahrain
🇧🇮 Burundi
🇧🇯 Benin
🇧🇱 St. Barthélemy
🇧🇲 Bermuda
🇧🇳 Brunei
🇧🇴 Bolivia
🇧🇶 Caribbean Netherlands
🇧🇷 Brazil
🇧🇸 Bahamas
🇧🇹 Bhutan
🇧🇻 Bouvet Island
🇧🇼 Botswana
🇧🇾 Belarus
🇧🇿 Belize
🇨🇦 Canada
🇨🇨 Cocos (Keeling) Islands
🇨🇩 Congo - Kinshasa
🇨🇫 Central African Republic
🇨🇬 Congo - Brazzaville
🇨🇭 Switzerland
🇨🇮 Côte d’Ivoire
🇨🇰 Cook Islands
🇨🇱 Chile
🇨🇲 Cameroon
🇨🇳 China
🇨🇴 Colombia
🇨🇵 Clipperton Island
🇨🇷 Costa Rica
🇨🇺 Cuba
🇨🇻 Cape Verde
🇨🇼 Curaçao
🇨🇽 Christmas Island
🇨🇾 Cyprus
🇨🇿 Czechia
🇩🇪 Germany
🇩🇬 Diego Garcia
🇩🇯 Djibouti
🇩🇰 Denmark
🇩🇲 Dominica
🇩🇴 Dominican Republic
🇩🇿 Algeria
🇪🇦 Ceuta &amp; Melilla
🇪🇨 Ecuador
🇪🇪 Estonia
🇪🇬 Egypt
🇪🇭 Western Sahara
🇪🇷 Eritrea
🇪🇸 Spain
🇪🇹 Ethiopia
🇪🇺 European Union
🇫🇮 Finland
🇫🇯 Fiji
🇫🇰 Falkland Islands
🇫🇲 Micronesia
🇫🇴 Faroe Islands
🇫🇷 France
🇬🇦 Gabon
🇬🇧 United Kingdom
🇬🇩 Grenada
🇬🇪 Georgia
🇬🇫 French Guiana
🇬🇬 Guernsey
🇬🇭 Ghana
🇬🇮 Gibraltar
🇬🇱 Greenland
🇬🇲 Gambia
🇬🇳 Guinea
🇬🇵 Guadeloupe
🇬🇶 Equatorial Guinea
🇬🇷 Greece
🇬🇸 South Georgia &amp; South Sandwich Islands
🇬🇹 Guatemala
🇬🇺 Guam
🇬🇼 Guinea-Bissau
🇬🇾 Guyana
🇭🇰 Hong Kong SAR China
🇭🇲 Heard &amp; McDonald Islands
🇭🇳 Honduras
🇭🇷 Croatia
🇭🇹 Haiti
🇭🇺 Hungary
🇮🇨 Canary Islands
🇮🇩 Indonesia
🇮🇪 Ireland
🇮🇱 Israel
🇮🇲 Isle of Man
🇮🇳 India
🇮🇴 British Indian Ocean Territory
🇮🇶 Iraq
🇮🇷 Iran
🇮🇸 Iceland
🇮🇹 Italy
🇯🇪 Jersey
🇯🇲 Jamaica
🇯🇴 Jordan
🇯🇵 Japan
🇰🇪 Kenya
🇰🇬 Kyrgyzstan
🇰🇭 Cambodia
🇰🇮 Kiribati
🇰🇲 Comoros
🇰🇳 St. Kitts &amp; Nevis
🇰🇵 North Korea
🇰🇷 South Korea
🇰🇼 Kuwait
🇰🇾 Cayman Islands
🇰🇿 Kazakhstan
🇱🇦 Laos
🇱🇧 Lebanon
🇱🇨 St. Lucia
🇱🇮 Liechtenstein
🇱🇰 Sri Lanka
🇱🇷 Liberia
🇱🇸 Lesotho
🇱🇹 Lithuania
🇱🇺 Luxembourg
🇱🇻 Latvia
🇱🇾 Libya
🇲🇦 Morocco
🇲🇨 Monaco
🇲🇩 Moldova
🇲🇪 Montenegro
🇲🇫 St. Martin
🇲🇬 Madagascar
🇲🇭 Marshall Islands
🇲🇰 Macedonia
🇲🇱 Mali
🇲🇲 Myanmar (Burma)
🇲🇳 Mongolia
🇲🇴 Macau SAR China
🇲🇵 Northern Mariana Islands
🇲🇶 Martinique
🇲🇷 Mauritania
🇲🇸 Montserrat
🇲🇹 Malta
🇲🇺 Mauritius
🇲🇻 Maldives
🇲🇼 Malawi
🇲🇽 Mexico
🇲🇾 Malaysia
🇲🇿 Mozambique
🇳🇦 Namibia
🇳🇨 New Caledonia
🇳🇪 Niger
🇳🇫 Norfolk Island
🇳🇬 Nigeria
🇳🇮 Nicaragua
🇳🇱 Netherlands
🇳🇴 Norway
🇳🇵 Nepal
🇳🇷 Nauru
🇳🇺 Niue
🇳🇿 New Zealand
🇴🇲 Oman
🇵🇦 Panama
🇵🇪 Peru
🇵🇫 French Polynesia
🇵🇬 Papua New Guinea
🇵🇭 Philippines
🇵🇰 Pakistan
🇵🇱 Poland
🇵🇲 St. Pierre &amp; Miquelon
🇵🇳 Pitcairn Islands
🇵🇷 Puerto Rico
🇵🇸 Palestinian Territories
🇵🇹 Portugal
🇵🇼 Palau
🇵🇾 Paraguay
🇶🇦 Qatar
🇷🇪 Réunion
🇷🇴 Romania
🇷🇸 Serbia
🇷🇺 Russia
🇷🇼 Rwanda
🇸🇦 Saudi Arabia
🇸🇧 Solomon Islands
🇸🇨 Seychelles
🇸🇩 Sudan
🇸🇪 Sweden
🇸🇬 Singapore
🇸🇭 St. Helena
🇸🇮 Slovenia
🇸🇯 Svalbard &amp; Jan Mayen
🇸🇰 Slovakia
🇸🇱 Sierra Leone
🇸🇲 San Marino
🇸🇳 Senegal
🇸🇴 Somalia
🇸🇷 Suriname
🇸🇸 South Sudan
🇸🇹 São Tomé &amp; Príncipe
🇸🇻 El Salvador
🇸🇽 Sint Maarten
🇸🇾 Syria
🇸🇿 Swaziland
🇹🇦 Tristan da Cunha
🇹🇨 Turks &amp; Caicos Islands
🇹🇩 Chad
🇹🇫 French Southern Territories
🇹🇬 Togo
🇹🇭 Thailand
🇹🇯 Tajikistan
🇹🇰 Tokelau
🇹🇱 Timor-Leste
🇹🇲 Turkmenistan
🇹🇳 Tunisia
🇹🇴 Tonga
🇹🇷 Turkey
🇹🇹 Trinidad &amp; Tobago
🇹🇻 Tuvalu
🇹🇼 Taiwan
🇹🇿 Tanzania
🇺🇦 Ukraine
🇺🇬 Uganda
🇺🇲 U.S. Outlying Islands
🇺🇳 United Nations
🇺🇸 United States
🇺🇾 Uruguay
🇺🇿 Uzbekistan
🇻🇦 Vatican City
🇻🇨 St. Vincent &amp; Grenadines
🇻🇪 Venezuela
🇻🇬 British Virgin Islands
🇻🇮 U.S. Virgin Islands
🇻🇳 Vietnam
🇻🇺 Vanuatu
🇼🇫 Wallis &amp; Futuna
🇼🇸 Samoa
🇽🇰 Kosovo
🇾🇪 Yemen
🇾🇹 Mayotte
🇿🇦 South Africa
🇿🇲 Zambia
🇿🇼 Zimbabwe
🏴󠁧󠁢󠁥󠁮󠁧󠁿 ⊛ England
🏴󠁧󠁢󠁳󠁣󠁴󠁿 ⊛ Scotland
🏴󠁧󠁢󠁷󠁬󠁳󠁿 ⊛ Wales
End-of-message
)

if [ "emoji" ]; then
    echo ${emoji%% *}
fi

