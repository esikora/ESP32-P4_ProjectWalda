// === Quiz data structures ====================================================

typedef struct {
    const char *question;
    const char *answer_a;
    const char *answer_b;
    const char *answer_c;
    char correct;            // 'A', 'B', 'C'
    char difficulty;         // 'L', 'M', 'H'
    const char *correct_reaction;
    const char *wrong_reaction;
} quiz_question_t;

quiz_question_t quiz_questions[] = {
    {
        "Was ist die Hauptstadt von Frankreich?",
        "Paris",
        "London",
        "Berlin",
        'A',
        'L',
        "Richtig! Paris ist die Hauptstadt von Frankreich.",
        "Falsch! Die richtige Antwort ist Paris."
    },
    {
        "Welcher Planet ist als der Rote Planet bekannt?",
        "Venus",
        "Mars",
        "Jupiter",
        'B',
        'L',
        "Richtig! Mars ist der Rote Planet.",
        "Falsch! Mars ist der Rote Planet."
    },
    {
        "Was ist 2 + 2?",
        "3",
        "4",
        "5",
        'B',
        'L',
        "Richtig! 2 + 2 = 4.",
        "Falsch! 2 + 2 = 4."
    },
    {
        "Wer schrieb 'Romeo und Julia'?",
        "Charles Dickens",
        "William Shakespeare",
        "Jane Austen",
        'B',
        'M',
        "Richtig! William Shakespeare schrieb 'Romeo und Julia'.",
        "Falsch! William Shakespeare schrieb 'Romeo und Julia'."
    },
    {
        "Welcher ist der größte Ozean der Erde?",
        "Atlantischer Ozean",
        "Indischer Ozean",
        "Pazifischer Ozean",
        'C',
        'M',
        "Richtig! Der Pazifische Ozean ist der größte.",
        "Falsch! Der Pazifische Ozean ist der größte."
    },
    {
        "In welchem Jahr endete der Zweite Weltkrieg?",
        "1944",
        "1945",
        "1946",
        'B',
        'M',
        "Richtig! Der Zweite Weltkrieg endete 1945.",
        "Falsch! Der Zweite Weltkrieg endete 1945."
    },
    {
        "Was ist das chemische Symbol für Gold?",
        "Go",
        "Gd",
        "Au",
        'C',
        'H',
        "Richtig! Au ist das chemische Symbol für Gold.",
        "Falsch! Au ist das chemische Symbol für Gold."
    },
    {
        "Welches Element hat die Ordnungszahl 1?",
        "Helium",
        "Wasserstoff",
        "Lithium",
        'B',
        'H',
        "Richtig! Wasserstoff hat die Ordnungszahl 1.",
        "Falsch! Wasserstoff hat die Ordnungszahl 1."
    },
    {
        "Wie lautet die Quadratwurzel von 144?",
        "12",
        "14",
        "16",
        'A',
        'H',
        "Richtig! Die Quadratwurzel von 144 ist 12.",
        "Falsch! Die Quadratwurzel von 144 ist 12."
    },
    {
        "Wer malte die Mona Lisa?",
        "Vincent van Gogh",
        "Leonardo da Vinci",
        "Pablo Picasso",
        'B',
        'H',
        "Richtig! Leonardo da Vinci malte die Mona Lisa.",
        "Falsch! Leonardo da Vinci malte die Mona Lisa."
    },
    // --- FILM ---
    {
        "Welcher Film gewann den Oscar für den besten Film im Jahr 1994?",
        "Forrest Gump",
        "Pulp Fiction",
        "Die Verurteilten",
        'A',
        'M',
        "Richtig! Forrest Gump gewann 1994 den Oscar für den besten Film.",
        "Falsch! Forrest Gump gewann 1994 den Oscar für den besten Film."
    },
    {
        "Wie heißt der Roboter aus dem Film 'Wall-E'?",
        "EVA",
        "WALL-E",
        "R2-D2",
        'B',
        'L',
        "Richtig! WALL-E ist der kleine Müllroboter aus dem Film.",
        "Falsch! WALL-E ist der kleine Müllroboter aus dem Film."
    },
    {
        "Welcher Schauspieler verkörpert Jack Sparrow in 'Fluch der Karibik'?",
        "Johnny Depp",
        "Orlando Bloom",
        "Hugh Jackman",
        'A',
        'L',
        "Richtig! Johnny Depp spielt Captain Jack Sparrow.",
        "Falsch! Johnny Depp spielt Captain Jack Sparrow."
    },
    {
        "In welchem Film sagt die Hauptfigur: 'Ich bin der König der Welt!'?",
        "Titanic",
        "Avatar",
        "Der Pate",
        'A',
        'L',
        "Richtig! Der Satz stammt aus dem Film Titanic.",
        "Falsch! Der Satz stammt aus dem Film Titanic."
    },
    {
        "Wie heißt der Löwe aus 'Der König der Löwen'?",
        "Scar",
        "Mufasa",
        "Simba",
        'C',
        'L',
        "Richtig! Simba ist der junge Löwe aus dem Film.",
        "Falsch! Simba ist der junge Löwe aus dem Film."
    },
    // --- MUSIK ---
    {
        "Welche Band schrieb den Hit 'Bohemian Rhapsody'?",
        "Queen",
        "The Beatles",
        "ABBA",
        'A',
        'M',
        "Richtig! 'Bohemian Rhapsody' stammt von Queen.",
        "Falsch! 'Bohemian Rhapsody' stammt von Queen."
    },
    {
        "Welches Instrument hat 88 Tasten?",
        "Gitarre",
        "Klavier",
        "Geige",
        'B',
        'L',
        "Richtig! Ein Klavier hat 88 Tasten.",
        "Falsch! Ein Klavier hat 88 Tasten."
    },
    {
        "Wer ist die Sängerin des Hits 'Rolling in the Deep'?",
        "Adele",
        "Rihanna",
        "Taylor Swift",
        'A',
        'L',
        "Richtig! Adele singt 'Rolling in the Deep'.",
        "Falsch! Adele singt 'Rolling in the Deep'."
    },
    {
        "Welche Musikrichtung stammt ursprünglich aus Jamaika?",
        "Reggae",
        "Jazz",
        "Techno",
        'A',
        'M',
        "Richtig! Reggae stammt aus Jamaika.",
        "Falsch! Reggae stammt aus Jamaika."
    },
    {
        "Welche deutsche Band ist für den Song 'Du hast' bekannt?",
        "Die Ärzte",
        "Rammstein",
        "Tokio Hotel",
        'B',
        'M',
        "Richtig! 'Du hast' ist einer der bekanntesten Songs von Rammstein.",
        "Falsch! 'Du hast' ist einer der bekanntesten Songs von Rammstein."
    },
    // --- BAYERN ---
    {
        "Wie heißt die Landeshauptstadt von Bayern?",
        "Nürnberg",
        "München",
        "Augsburg",
        'B',
        'L',
        "Richtig! München ist die Landeshauptstadt von Bayern.",
        "Falsch! München ist die Landeshauptstadt von Bayern."
    },
    {
        "Welches Schloss ließ König Ludwig II. erbauen?",
        "Schloss Neuschwanstein",
        "Schloss Bellevue",
        "Schloss Schönbrunn",
        'A',
        'L',
        "Richtig! Schloss Neuschwanstein wurde von König Ludwig II. erbaut.",
        "Falsch! Schloss Neuschwanstein wurde von König Ludwig II. erbaut."
    },
    {
        "Wie nennt man in Bayern ein Brötchen?",
        "Schrippe",
        "Semmel",
        "Weckle",
        'B',
        'L',
        "Richtig! In Bayern sagt man 'Semmel'.",
        "Falsch! In Bayern sagt man 'Semmel'."
    },
    {
        "Welcher Fluss fließt durch Ingolstadt?",
        "Donau",
        "Isar",
        "Lech",
        'A',
        'L',
        "Richtig! Die Donau fließt durch Ingolstadt.",
        "Falsch! Die Donau fließt durch Ingolstadt."
    },
    {
        "Wie heißt das größte Volksfest in Bayern?",
        "Cannstatter Wasen",
        "Oktoberfest",
        "Gäubodenfest",
        'B',
        'L',
        "Richtig! Das Oktoberfest ist das größte Volksfest in Bayern.",
        "Falsch! Das Oktoberfest ist das größte Volksfest in Bayern."
    },
    // --- DISNEY ---
    {
        "Wie heißt die Meerjungfrau in 'Arielle'?",
        "Belle",
        "Arielle",
        "Jasmine",
        'B',
        'L',
        "Richtig! Arielle ist die kleine Meerjungfrau.",
        "Falsch! Arielle ist die kleine Meerjungfrau."
    },
    {
        "Welches Tier ist Bambi?",
        "Reh",
        "Hase",
        "Fuchs",
        'A',
        'L',
        "Richtig! Bambi ist ein Rehkitz.",
        "Falsch! Bambi ist ein Rehkitz."
    },
    {
        "Wie heißt der Schneemann aus 'Die Eiskönigin'?",
        "Sven",
        "Olaf",
        "Kristoff",
        'B',
        'L',
        "Richtig! Olaf ist der fröhliche Schneemann.",
        "Falsch! Olaf ist der fröhliche Schneemann."
    },
    {
        "Welche Disney-Prinzessin hat einen Tiger namens Rajah?",
        "Pocahontas",
        "Mulan",
        "Jasmine",
        'C',
        'M',
        "Richtig! Jasmine hat einen Tiger namens Rajah.",
        "Falsch! Jasmine hat einen Tiger namens Rajah."
    },
    {
        "Wie heißt der Junge, der mit Baloo im Dschungel lebt?",
        "Mogli",
        "Aladdin",
        "Peter Pan",
        'A',
        'L',
        "Richtig! Mogli lebt mit Baloo im Dschungel.",
        "Falsch! Mogli lebt mit Baloo im Dschungel."
    }
};

#define NUM_QUIZ_QUESTIONS (sizeof(quiz_questions) / sizeof(quiz_question_t))
