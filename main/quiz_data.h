#ifndef QUIZ_DATA_H
#define QUIZ_DATA_H

// ===============================================
//  Quiz Categories
// ===============================================
typedef enum {
    CAT_ALLGEMEIN,
    CAT_GEOGRAFIE,
    CAT_GESCHICHTE,
    CAT_NATUR,
    CAT_FILM,
    CAT_MUSIK,
    CAT_SPORT,
    CAT_BAYERN,
    CAT_DISNEY,
    CAT_TECHNIK,
    CAT_GEOCACHING
} quiz_category_t;

// ===============================================
//  Quiz Question Structure
// ===============================================
typedef struct {
    const char *question;
    const char *answer_a;
    const char *answer_b;
    const char *answer_c;
    char correct;           // 'A', 'B', 'C'
    char difficulty;        // 'L', 'M', 'H'
    quiz_category_t category;
    const char *correct_reaction;
    const char *wrong_reaction;
} quiz_question_t;

// ===============================================
//  Quiz Questions (100 total)
// ===============================================
quiz_question_t quiz_questions[] = {
    { "Wie viele Tage hat ein Schaltjahr?", "365", "366", "367", 'B', 'L', CAT_ALLGEMEIN, "Richtig! Ein Schaltjahr hat 366 Tage.", "Falsch! Ein Schaltjahr hat 366 Tage." },
    { "Welche Farbe entsteht aus Blau und Gelb?", "Grün", "Orange", "Violett", 'A', 'L', CAT_ALLGEMEIN, "Richtig! Blau und Gelb ergeben Grün.", "Falsch! Blau und Gelb ergeben Grün." },
    { "Wie viele Kontinente gibt es?", "Acht", "Drei", "Sieben", 'C', 'M', CAT_ALLGEMEIN, "Richtig! Es gibt sieben Kontinente.", "Falsch! Es gibt sieben Kontinente." },
    { "Welches Tier ist das größte an Land?", "Elefant", "Giraffe", "Nashorn", 'A', 'L', CAT_ALLGEMEIN, "Richtig! Der Elefant ist das größte Landtier.", "Falsch! Der Elefant ist das größte Landtier." },
    { "Wie viele Planeten hat unser Sonnensystem?", "Acht", "Neun", "Sieben", 'A', 'M', CAT_ALLGEMEIN, "Richtig! Es sind acht Planeten.", "Falsch! Es sind acht Planeten." },
    { "Welche Sprache hat weltweit die meisten Muttersprachler?", "Englisch", "Mandarin", "Spanisch", 'B', 'M', CAT_ALLGEMEIN, "Richtig! Mandarin hat die meisten Muttersprachler.", "Falsch! Mandarin hat die meisten Muttersprachler." },
    { "Wie viele Bundesländer hat Deutschland?", "14", "15", "16", 'C', 'L', CAT_ALLGEMEIN, "Richtig! Deutschland hat 16 Bundesländer.", "Falsch! Deutschland hat 16 Bundesländer." },
    { "Welches Metall leitet Strom am besten?", "Kupfer", "Silber", "Gold", 'B', 'H', CAT_ALLGEMEIN, "Richtig! Silber ist der beste Leiter.", "Falsch! Silber ist der beste Leiter." },
    { "Wie viele Zähne hat ein erwachsener Mensch?", "28", "30", "32", 'C', 'M', CAT_ALLGEMEIN, "Richtig! Erwachsene haben 32 Zähne.", "Falsch! Erwachsene haben 32 Zähne." },
    { "Welches Tier legt Eier?", "Krokodil", "Fledermaus", "Delfin", 'A', 'L', CAT_ALLGEMEIN, "Richtig! Krokodile legen Eier.", "Falsch! Krokodile legen Eier." },
    { "Welcher ist der längste Fluss der Welt?", "Nil", "Amazonas", "Jangtse", 'B', 'H', CAT_GEOGRAFIE, "Richtig! Der Amazonas ist der längste Fluss.", "Falsch! Der Amazonas ist der längste Fluss." },
    { "Welches Land hat die größte Bevölkerung?", "China", "Indien", "USA", 'B', 'M', CAT_GEOGRAFIE, "Richtig! Indien hat die größte Bevölkerung.", "Falsch! Indien hat die größte Bevölkerung." },
    { "Welche Stadt liegt an der Themse?", "London", "Paris", "Rom", 'A', 'L', CAT_GEOGRAFIE, "Richtig! London liegt an der Themse.", "Falsch! London liegt an der Themse." },
    { "Welcher Kontinent ist der heißeste?", "Afrika", "Australien", "Südamerika", 'A', 'L', CAT_GEOGRAFIE, "Richtig! Afrika ist der heißeste Kontinent.", "Falsch! Afrika ist der heißeste Kontinent." },
    { "Welches Land hat die Form eines Stiefels?", "Spanien", "Italien", "Portugal", 'B', 'L', CAT_GEOGRAFIE, "Richtig! Italien hat die Form eines Stiefels.", "Falsch! Italien hat die Form eines Stiefels." },
    { "Welches Meer liegt zwischen Europa und Afrika?", "Mittelmeer", "Schwarzes Meer", "Rotes Meer", 'A', 'L', CAT_GEOGRAFIE, "Richtig! Das Mittelmeer liegt zwischen Europa und Afrika.", "Falsch! Das Mittelmeer liegt zwischen Europa und Afrika." },
    { "Welche Hauptstadt liegt am weitesten nördlich?", "Oslo", "Helsinki", "Reykjavik", 'C', 'H', CAT_GEOGRAFIE, "Richtig! Reykjavik ist die nördlichste Hauptstadt.", "Falsch! Reykjavik ist die nördlichste Hauptstadt." },
    { "Welches Land hat die größte Fläche?", "Kanada", "China", "Russland", 'C', 'M', CAT_GEOGRAFIE, "Richtig! Russland ist das flächengrößte Land.", "Falsch! Russland ist das flächengrößte Land." },
    { "Welcher Berg ist der höchste der Welt?", "K2", "Kangchendzönga", "Mount Everest", 'C', 'L', CAT_GEOGRAFIE, "Richtig! Der Mount Everest ist der höchste Berg.", "Falsch! Der Mount Everest ist der höchste Berg." },
    { "Welches Land hat die meisten Inseln?", "Schweden", "Indonesien", "Japan", 'A', 'H', CAT_GEOGRAFIE, "Richtig! Schweden hat die meisten Inseln.", "Falsch! Schweden hat die meisten Inseln." },
    { "In welchem Jahr fiel die Berliner Mauer?", "1987", "1989", "1991", 'B', 'L', CAT_GESCHICHTE, "Richtig! Die Mauer fiel 1989.", "Falsch! Die Mauer fiel 1989." },
    { "Wer war der erste Mensch im Weltraum?", "Neil Armstrong", "Juri Gagarin", "Buzz Aldrin", 'B', 'M', CAT_GESCHICHTE, "Richtig! Juri Gagarin war der erste Mensch im All.", "Falsch! Juri Gagarin war der erste Mensch im All." },
    { "Welches Reich baute die Pyramiden?", "Römisches Reich", "Ägyptisches Reich", "Persisches Reich", 'B', 'L', CAT_GESCHICHTE, "Richtig! Die Pyramiden stammen aus dem alten Ägypten.", "Falsch! Die Pyramiden stammen aus dem alten Ägypten." },
    { "Wer war der erste Bundeskanzler Deutschlands?", "Konrad Adenauer", "Willy Brandt", "Helmut Kohl", 'A', 'M', CAT_GESCHICHTE, "Richtig! Konrad Adenauer war der erste Bundeskanzler.", "Falsch! Konrad Adenauer war der erste Bundeskanzler." },
    { "Welche Stadt wurde 79 n. Chr. vom Vesuv zerstört?", "Pompeji", "Athen", "Karthago", 'A', 'L', CAT_GESCHICHTE, "Richtig! Pompeji wurde durch den Vesuv zerstört.", "Falsch! Pompeji wurde durch den Vesuv zerstört." },
    { "Wer entdeckte Amerika?", "Christoph Kolumbus", "Marco Polo", "James Cook", 'A', 'L', CAT_GESCHICHTE, "Richtig! Kolumbus erreichte Amerika 1492.", "Falsch! Kolumbus erreichte Amerika 1492." },
    { "Welches Land begann den Ersten Weltkrieg?", "Österreich-Ungarn", "Deutschland", "Frankreich", 'A', 'H', CAT_GESCHICHTE, "Richtig! Österreich-Ungarn erklärte zuerst den Krieg.", "Falsch! Österreich-Ungarn erklärte zuerst den Krieg." },
    { "Wer erfand den Buchdruck?", "Isaac Newton", "Leonardo da Vinci", "Johannes Gutenberg", 'C', 'M', CAT_GESCHICHTE, "Richtig! Gutenberg erfand den modernen Buchdruck.", "Falsch! Gutenberg erfand den modernen Buchdruck." },
    { "Welche Epoche folgte auf das Mittelalter?", "Antike", "Barock", "Renaissance", 'C', 'M', CAT_GESCHICHTE, "Richtig! Die Renaissance folgte auf das Mittelalter.", "Falsch! Die Renaissance folgte auf das Mittelalter." },
    { "Wer war der erste Mensch auf dem Mond?", "Alan Shepard", "Michael Collins", "Neil Armstrong", 'C', 'L', CAT_GESCHICHTE, "Richtig! Neil Armstrong betrat 1969 den Mond.", "Falsch! Neil Armstrong betrat 1969 den Mond." },
    { "Welches Gas atmen wir hauptsächlich ein?", "Sauerstoff", "Stickstoff", "Kohlenstoffdioxid", 'B', 'L', CAT_NATUR, "Richtig! Die Luft besteht zu 78% aus Stickstoff.", "Falsch! Die Luft besteht zu 78% aus Stickstoff." },
    { "Wie viele Beine hat ein Insekt?", "Vier", "Sechs", "Acht", 'B', 'L', CAT_NATUR, "Richtig! Insekten haben sechs Beine.", "Falsch! Insekten haben sechs Beine." },
    { "Welcher Planet ist der heißeste?", "Venus", "Merkur", "Mars", 'A', 'M', CAT_NATUR, "Richtig! Die Venus ist der heißeste Planet.", "Falsch! Die Venus ist der heißeste Planet." },
    { "Wie nennt man die Lehre vom Verhalten der Tiere?", "Ökologie", "Ethologie", "Zoologie", 'B', 'H', CAT_NATUR, "Richtig! Ethologie ist die Verhaltensforschung.", "Falsch! Ethologie ist die Verhaltensforschung." },
    { "Welches Element hat das Symbol O?", "Osmium", "Ozon", "Sauerstoff", 'C', 'L', CAT_NATUR, "Richtig! O steht für Sauerstoff.", "Falsch! O steht für Sauerstoff." },
    { "Wie viele Chromosomen hat der Mensch?", "46", "44", "48", 'A', 'H', CAT_NATUR, "Richtig! Der Mensch hat 46 Chromosomen.", "Falsch! Der Mensch hat 46 Chromosomen." },
    { "Welches Tier ist ein Säugetier?", "Hai", "Pinguin", "Delfin", 'C', 'L', CAT_NATUR, "Richtig! Delfine sind Säugetiere.", "Falsch! Delfine sind Säugetiere." },
    { "Wie nennt man flüssiges Gestein im Erdinneren?", "Magma", "Lava", "Basalt", 'A', 'M', CAT_NATUR, "Richtig! Unter der Erde heißt es Magma.", "Falsch! Unter der Erde heißt es Magma." },
    { "Welcher Stoff ist für die grüne Farbe der Pflanzen verantwortlich?", "Chlorophyll", "Glukose", "Zellulose", 'A', 'M', CAT_NATUR, "Richtig! Chlorophyll färbt Pflanzen grün.", "Falsch! Chlorophyll färbt Pflanzen grün." },
    { "Wie nennt man die kleinste Einheit des Lebens?", "Molekül", "Atom", "Zelle", 'C', 'L', CAT_NATUR, "Richtig! Die Zelle ist die kleinste Lebenseinheit.", "Falsch! Die Zelle ist die kleinste Lebenseinheit." },
    { "Wer spielt Iron Man im Marvel-Universum?", "Chris Evans", "Robert Downey Jr.", "Chris Hemsworth", 'B', 'L', CAT_FILM, "Richtig! Robert Downey Jr. spielt Iron Man.", "Falsch! Robert Downey Jr. spielt Iron Man." },
    { "Wie heißt der Zauberschüler in Hogwarts?", "Harry Potter", "Hairy Potter", "Harry Plotter", 'A', 'L', CAT_FILM, "Richtig! Harry Potter ist der Zauberschüler.", "Falsch! Harry Potter ist der Zauberschüler." },
    { "Welcher Film enthält den Satz 'Möge die Macht mit dir sein'?", "Star Trek", "Star Wars", "Matrix", 'B', 'L', CAT_FILM, "Richtig! Der Satz stammt aus Star Wars.", "Falsch! Der Satz stammt aus Star Wars." },
    { "Wie heißt der Drache aus 'Drachenzähmen leicht gemacht'?", "Ohnezahn", "Falkor", "Smaug", 'A', 'M', CAT_FILM, "Richtig! Ohnezahn ist der Drache.", "Falsch! Ohnezahn ist der Drache." },
    { "Wer spielt den Joker in 'The Dark Knight'?", "Heath Ledger", "Joaquin Phoenix", "Jared Leto", 'A', 'H', CAT_FILM, "Richtig! Heath Ledger spielte den Joker.", "Falsch! Heath Ledger spielte den Joker." },
    { "Wie heißt der Fischvater in 'Findet Nemo'?", "Bruce", "Dory", "Marlin", 'C', 'L', CAT_FILM, "Richtig! Marlin ist Nemos Vater.", "Falsch! Marlin ist Nemos Vater." },
    { "Welcher Film gewann 2020 den Oscar für den besten Film?", "Joker", "Parasite", "1917", 'B', 'H', CAT_FILM, "Richtig! Parasite gewann 2020 den Oscar.", "Falsch! Parasite gewann 2020 den Oscar." },
    { "Wie heißt der Cowboy aus Toy Story?", "Jessie", "Buzz", "Woody", 'C', 'L', CAT_FILM, "Richtig! Woody ist der Cowboy.", "Falsch! Woody ist der Cowboy." },
    { "Welche Serie spielt in Westeros?", "Game of Thrones", "Vikings", "The Witcher", 'A', 'M', CAT_FILM, "Richtig! Game of Thrones spielt in Westeros.", "Falsch! Game of Thrones spielt in Westeros." },
    { "Wie heißt der Schneemann aus 'Die Eiskönigin'?", "Sven", "Kristoff", "Olaf", 'C', 'L', CAT_FILM, "Richtig! Olaf ist der Schneemann.", "Falsch! Olaf ist der Schneemann." },
    { "Wer sang den Hit 'Thriller'?", "Michael Jackson", "Prince", "Stevie Wonder", 'A', 'L', CAT_MUSIK, "Richtig! Michael Jackson sang 'Thriller'.", "Falsch! Michael Jackson sang 'Thriller'." },
    { "Welche Band schrieb 'Hotel California'?", "Eagles", "Queen", "Pink Floyd", 'A', 'M', CAT_MUSIK, "Richtig! 'Hotel California' stammt von den Eagles.", "Falsch! 'Hotel California' stammt von den Eagles." },
    { "Welches Instrument hat Saiten?", "Trompete", "Geige", "Schlagzeug", 'B', 'L', CAT_MUSIK, "Richtig! Die Geige hat Saiten.", "Falsch! Die Geige hat Saiten." },
    { "Wer ist die Sängerin von 'Bad Romance'?", "Lady Gaga", "Katy Perry", "Ariana Grande", 'A', 'L', CAT_MUSIK, "Richtig! Lady Gaga singt 'Bad Romance'.", "Falsch! Lady Gaga singt 'Bad Romance'." },
    { "Welche Musikrichtung ist typisch für Jamaika?", "Blues", "Rock", "Reggae", 'C', 'M', CAT_MUSIK, "Richtig! Reggae stammt aus Jamaika.", "Falsch! Reggae stammt aus Jamaika." },
    { "Welche deutsche Band schrieb 'Wind of Change'?", "Die Toten Hosen", "Rammstein", "Scorpions", 'C', 'M', CAT_MUSIK, "Richtig! Die Scorpions sangen 'Wind of Change'.", "Falsch! Die Scorpions sangen 'Wind of Change'." },
    { "Wer ist der Komponist der 9. Sinfonie?", "Mozart", "Beethoven", "Bach", 'B', 'H', CAT_MUSIK, "Richtig! Beethoven schrieb die 9. Sinfonie.", "Falsch! Beethoven schrieb die 9. Sinfonie." },
    { "Welcher Sänger ist bekannt für den Moonwalk?", "Elvis Presley", "Michael Jackson", "Bruno Mars", 'B', 'L', CAT_MUSIK, "Richtig! Michael Jackson machte den Moonwalk berühmt.", "Falsch! Michael Jackson machte den Moonwalk berühmt." },
    { "Welche Band veröffentlichte das Album 'The Dark Side of the Moon'?", "Metallica", "The Rolling Stones", "Pink Floyd", 'C', 'H', CAT_MUSIK, "Richtig! Pink Floyd veröffentlichte das Album.", "Falsch! Pink Floyd veröffentlichte das Album." },
    { "Welches Instrument spielt man mit einem Bogen?", "Geige", "Klavier", "Trommel", 'A', 'L', CAT_MUSIK, "Richtig! Die Geige wird mit einem Bogen gespielt.", "Falsch! Die Geige wird mit einem Bogen gespielt." },
    { "Wie viele Spieler hat eine Fußballmannschaft auf dem Feld?", "11", "10", "12", 'A', 'L', CAT_SPORT, "Richtig! Eine Mannschaft hat 11 Spieler.", "Falsch! Eine Mannschaft hat 11 Spieler." },
    { "Wie viele Minuten dauert ein reguläres Fußballspiel?", "80", "90", "100", 'B', 'L', CAT_SPORT, "Richtig! Ein Spiel dauert 90 Minuten.", "Falsch! Ein Spiel dauert 90 Minuten." },
    { "Welche Sportart wird bei Wimbledon gespielt?", "Tennis", "Badminton", "Cricket", 'A', 'L', CAT_SPORT, "Richtig! Wimbledon ist ein Tennisturnier.", "Falsch! Wimbledon ist ein Tennisturnier." },
    { "Wie viele Ringe hat das olympische Symbol?", "4", "5", "6", 'B', 'M', CAT_SPORT, "Richtig! Das Symbol hat 5 Ringe.", "Falsch! Das Symbol hat 5 Ringe." },
    { "Welche Sportart betreibt Lewis Hamilton?", "Formel 1", "MotoGP", "Rallye", 'A', 'M', CAT_SPORT, "Richtig! Hamilton fährt Formel 1.", "Falsch! Hamilton fährt Formel 1." },
    { "Wie viele Punkte gibt ein Touchdown im American Football?", "6", "3", "1", 'A', 'M', CAT_SPORT, "Richtig! Ein Touchdown zählt 6 Punkte.", "Falsch! Ein Touchdown zählt 6 Punkte." },
    { "Welche Sportart wird mit einem Shuttlecock gespielt?", "Squash", "Tennis", "Badminton", 'C', 'M', CAT_SPORT, "Richtig! Badminton wird mit einem Shuttlecock gespielt.", "Falsch! Badminton wird mit einem Shuttlecock gespielt." },
    { "Wie viele Spieler stehen beim Volleyball pro Team auf dem Feld?", "7", "6", "5", 'B', 'L', CAT_SPORT, "Richtig! Ein Volleyballteam hat 6 Spieler.", "Falsch! Ein Volleyballteam hat 6 Spieler." },
    { "Welche Nation gewann 2014 die Fußball-WM?", "Spanien", "Brasilien", "Deutschland", 'C', 'L', CAT_SPORT, "Richtig! Deutschland gewann 2014 die WM.", "Falsch! Deutschland gewann 2014 die WM." },
    { "Welche Sportart betreibt Serena Williams?", "Leichtathletik", "Golf", "Tennis", 'C', 'L', CAT_SPORT, "Richtig! Serena Williams ist Tennisspielerin.", "Falsch! Serena Williams ist Tennisspielerin." },
    { "Wie heißt das größte Volksfest in Bayern?", "Cannstatter Wasen", "Oktoberfest", "Gäubodenfest", 'B', 'L', CAT_BAYERN, "Richtig! Das Oktoberfest ist das größte Volksfest.", "Falsch! Das Oktoberfest ist das größte Volksfest." },
    { "Wie nennt man in Bayern ein Brötchen?", "Schrippe", "Semmel", "Weckle", 'B', 'L', CAT_BAYERN, "Richtig! In Bayern sagt man Semmel.", "Falsch! In Bayern sagt man Semmel." },
    { "Welcher Fluss fließt durch Ingolstadt?", "Donau", "Isar", "Lech", 'A', 'L', CAT_BAYERN, "Richtig! Die Donau fließt durch Ingolstadt.", "Falsch! Die Donau fließt durch Ingolstadt." },
    { "Welches Schloss ließ König Ludwig II. erbauen?", "Schloss Neuschwanstein", "Schloss Bellevue", "Schloss Schönbrunn", 'A', 'L', CAT_BAYERN, "Richtig! Schloss Neuschwanstein stammt von Ludwig II.", "Falsch! Schloss Neuschwanstein stammt von Ludwig II." },
    { "Wie heißt die Landeshauptstadt von Bayern?", "Nürnberg", "München", "Augsburg", 'B', 'L', CAT_BAYERN, "Richtig! München ist die Landeshauptstadt.", "Falsch! München ist die Landeshauptstadt." },
    { "Wie heißt das bayerische Nationalgericht?", "Weißwurst", "Currywurst", "Bratwurst", 'A', 'M', CAT_BAYERN, "Richtig! Die Weißwurst ist typisch bayerisch.", "Falsch! Die Weißwurst ist typisch bayerisch." },
    { "Wie nennt man das bayerische Bierglas mit 1 Liter Inhalt?", "Maß", "Halbe", "Krügerl", 'A', 'L', CAT_BAYERN, "Richtig! Eine Maß fasst 1 Liter.", "Falsch! Eine Maß fasst 1 Liter." },
    { "Welche Stadt ist für die BMW-Produktion bekannt?", "Passau", "Regensburg", "München", 'C', 'M', CAT_BAYERN, "Richtig! BMW hat seinen Hauptsitz in München.", "Falsch! BMW hat seinen Hauptsitz in München." },
    { "Wie heißt der höchste Berg Bayerns?", "Watzmann", "Hochkalter", "Zugspitze", 'C', 'H', CAT_BAYERN, "Richtig! Die Zugspitze ist der höchste Berg.", "Falsch! Die Zugspitze ist der höchste Berg." },
    { "Welche bayerische Stadt ist für die Festung Marienberg bekannt?", "Kempten", "Regensburg", "Würzburg", 'C', 'M', CAT_BAYERN, "Richtig! Die Festung Marienberg steht in Würzburg.", "Falsch! Die Festung Marienberg steht in Würzburg." },
    { "Wie heißt die Meerjungfrau in 'Arielle'?", "Belle", "Arielle", "Jasmine", 'B', 'L', CAT_DISNEY, "Richtig! Arielle ist die kleine Meerjungfrau.", "Falsch! Arielle ist die kleine Meerjungfrau." },
    { "Welches Tier ist Bambi?", "Reh", "Hase", "Fuchs", 'A', 'L', CAT_DISNEY, "Richtig! Bambi ist ein Rehkitz.", "Falsch! Bambi ist ein Rehkitz." },
    { "Wie heißt der Schneemann aus 'Die Eiskönigin'?", "Sven", "Olaf", "Kristoff", 'B', 'L', CAT_DISNEY, "Richtig! Olaf ist der Schneemann.", "Falsch! Olaf ist der Schneemann." },
    { "Welche Disney-Prinzessin hat einen Tiger namens Rajah?", "Pocahontas", "Mulan", "Jasmine", 'C', 'M', CAT_DISNEY, "Richtig! Jasmine hat einen Tiger namens Rajah.", "Falsch! Jasmine hat einen Tiger namens Rajah." },
    { "Wie heißt der Junge, der mit Baloo im Dschungel lebt?", "Mogli", "Aladdin", "Peter Pan", 'A', 'L', CAT_DISNEY, "Richtig! Mogli lebt mit Baloo im Dschungel.", "Falsch! Mogli lebt mit Baloo im Dschungel." },
    { "Wie heißt der Vater von Simba?", "Scar", "Mufasa", "Zazu", 'B', 'L', CAT_DISNEY, "Richtig! Mufasa ist Simbas Vater.", "Falsch! Mufasa ist Simbas Vater." },
    { "Welche Figur trägt eine rote Hose mit zwei weißen Knöpfen?", "Micky Maus", "Donald Duck", "Goofy", 'A', 'L', CAT_DISNEY, "Richtig! Micky Maus trägt die rote Hose.", "Falsch! Micky Maus trägt die rote Hose." },
    { "Wie heißt der Drache aus Mulan?", "Mushu", "Shen", "Khan", 'A', 'M', CAT_DISNEY, "Richtig! Mushu ist der kleine Drache.", "Falsch! Mushu ist der kleine Drache." },
    { "Welche Disney-Figur verliert ihren Schuh?", "Arielle", "Belle", "Cinderella", 'C', 'L', CAT_DISNEY, "Richtig! Cinderella verliert ihren Schuh.", "Falsch! Cinderella verliert ihren Schuh." },
    { "Wie heißt der Hund von Mickey Maus?", "Goofy", "Max", "Pluto", 'C', 'L', CAT_DISNEY, "Richtig! Pluto ist Mickeys Hund.", "Falsch! Pluto ist Mickeys Hund." },
    { "Was bedeutet die Abkürzung CPU?", "Central Processing Unit", "Computer Power Unit", "Control Program Utility", 'A', 'M', CAT_TECHNIK, "Richtig! CPU steht für Central Processing Unit.", "Falsch! CPU steht für Central Processing Unit." },
    { "Welches Betriebssystem wird von Apple entwickelt?", "Windows", "macOS", "Linux", 'B', 'L', CAT_TECHNIK, "Richtig! macOS stammt von Apple.", "Falsch! macOS stammt von Apple." },
    { "Welche Einheit misst die Taktfrequenz eines Prozessors?", "Hertz", "Watt", "Volt", 'A', 'L', CAT_TECHNIK, "Richtig! Die Taktfrequenz wird in Hertz gemessen.", "Falsch! Die Taktfrequenz wird in Hertz gemessen." },
    { "Welches Gerät speichert Daten dauerhaft?", "RAM", "SSD", "Cache", 'B', 'L', CAT_TECHNIK, "Richtig! Eine SSD speichert Daten dauerhaft.", "Falsch! Eine SSD speichert Daten dauerhaft." },
    { "Was ist HTML?", "Eine Programmiersprache", "Eine Auszeichnungssprache", "Ein Betriebssystem", 'B', 'M', CAT_TECHNIK, "Richtig! HTML ist eine Auszeichnungssprache.", "Falsch! HTML ist eine Auszeichnungssprache." },
    { "Welche Firma entwickelte das Android-Betriebssystem?", "Google", "Samsung", "IBM", 'A', 'M', CAT_TECHNIK, "Richtig! Android wurde von Google entwickelt.", "Falsch! Android wurde von Google entwickelt." },
    { "Was bedeutet die Abkürzung GPU?", "Graphics Processing Unit", "General Processing Unit", "Graphical Program Utility", 'A', 'M', CAT_TECHNIK, "Richtig! GPU steht für Graphics Processing Unit.", "Falsch! GPU steht für Graphics Processing Unit." },
    { "Welches Gerät dient zur Eingabe?", "Monitor", "Lautsprecher", "Maus", 'C', 'L', CAT_TECHNIK, "Richtig! Die Maus ist ein Eingabegerät.", "Falsch! Die Maus ist ein Eingabegerät." },
    { "Was ist Open Source?", "Kostenlose Software", "Software ohne Lizenz", "Quelloffene Software", 'C', 'H', CAT_TECHNIK, "Richtig! Open Source bedeutet quelloffen.", "Falsch! Open Source bedeutet quelloffen." },
    { "Welche Programmiersprache wird oft für Webentwicklung genutzt?", "Python", "C", "JavaScript", 'C', 'L', CAT_TECHNIK, "Richtig! JavaScript wird häufig im Web genutzt.", "Falsch! JavaScript wird häufig im Web genutzt." },
    {
        "Was ist Geocaching?",
        "Eine GPS-basierte Schatzsuche", "Ein Kartenspiel", "Ein Navigationsfehler",
        'A','L', CAT_GEOCACHING,
        "Richtig! Geocaching ist eine GPS-basierte Schatzsuche.",
        "Falsch! Geocaching ist eine GPS-basierte Schatzsuche."
    },
    {
        "Wann wurde Geocaching offiziell gestartet?",
        "2000", "1995", "2005",
        'A','M', CAT_GEOCACHING,
        "Richtig! Geocaching begann im Jahr 2000.",
        "Falsch! Geocaching begann im Jahr 2000."
    },
    {
        "Was feiert der Blue Switch Day?",
        "Abschaltung von Selective Availability", "Erfindung des GPS", "Start von Project A.P.E.",
        'A','H', CAT_GEOCACHING,
        "Richtig! 2000 wurde Selective Availability deaktiviert.",
        "Falsch! Es geht um die Abschaltung von Selective Availability."
    },
    {
        "Welche Firma betreibt geocaching.com?",
        "Groundspeak", "Geoworld", "CacheCorp",
        'A','L', CAT_GEOCACHING,
        "Richtig! Groundspeak betreibt geocaching.com.",
        "Falsch! Groundspeak betreibt geocaching.com."
    },
    {
        "Was ist ein Traditional Cache?",
        "Ein Cache an den veröffentlichten Koordinaten", "Ein Cache ohne Dose", "Ein Cache mit mehreren Stationen",
        'A','L', CAT_GEOCACHING,
        "Richtig! Traditionals liegen direkt an den Koordinaten.",
        "Falsch! Traditionals liegen direkt an den Koordinaten."
    },
    {
        "Was ist ein Multi-Cache?",
        "Ein Cache mit mehreren Stationen", "Ein Cache ohne Logbuch", "Ein Cache mit Webcam",
        'A','M', CAT_GEOCACHING,
        "Richtig! Multis haben mehrere Stationen.",
        "Falsch! Multis haben mehrere Stationen."
    },
    {
        "Was ist ein Mystery-Cache?",
        "Ein Rätsel-Cache", "Ein Cache im Wasser", "Ein Cache ohne Koordinaten",
        'A','M', CAT_GEOCACHING,
        "Richtig! Mystery-Caches erfordern ein Rätsel.",
        "Falsch! Mystery-Caches erfordern ein Rätsel."
    },
    {
        "Was ist ein EarthCache?",
        "Ein Cache ohne Dose mit geologischen Aufgaben", "Ein Cache im Weltall", "Ein Cache mit Metallbehälter",
        'A','H', CAT_GEOCACHING,
        "Richtig! EarthCaches haben keine Dose und vermitteln Geologie.",
        "Falsch! EarthCaches haben keine Dose und vermitteln Geologie."
    },
    {
        "Was ist ein Letterbox Hybrid?",
        "Ein Cache mit Stempel", "Ein Cache ohne Koordinaten", "Ein Cache mit Webcam",
        'A','M', CAT_GEOCACHING,
        "Richtig! Letterbox Hybrids enthalten einen Stempel.",
        "Falsch! Letterbox Hybrids enthalten einen Stempel."
    },
    {
        "Was ist ein Event-Cache?",
        "Ein Treffen von Geocachern", "Ein Cache ohne Dose", "Ein Cache mit mehreren Stationen",
        'A','L', CAT_GEOCACHING,
        "Richtig! Event-Caches sind Treffen von Geocachern.",
        "Falsch! Event-Caches sind Treffen von Geocachern."
    },
    {
        "Was ist ein CITO-Event?",
        "Ein Umweltreinigungs-Event", "Ein Trackable-Tausch", "Ein Reviewer-Treffen",
        'A','L', CAT_GEOCACHING,
        "Richtig! CITO-Events dienen der Umwelt.",
        "Falsch! CITO-Events sind Umweltaktionen."
    },
    {
        "Wie viele Teilnehmer braucht ein MEGA-Event?",
        "500+", "1000+", "250+",
        'A','M', CAT_GEOCACHING,
        "Richtig! Mega-Events haben mindestens 500 Teilnehmer.",
        "Falsch! Mega-Events haben mindestens 500 Teilnehmer."
    },
    {
        "Wie viele Teilnehmer braucht ein GIGA-Event?",
        "5000+", "1000+", "2500+",
        'A','H', CAT_GEOCACHING,
        "Richtig! Giga-Events haben mindestens 5000 Teilnehmer.",
        "Falsch! Giga-Events haben mindestens 5000 Teilnehmer."
    },
    {
        "Was ist ein Wherigo-Cache?",
        "Ein Cartridge-basiertes GPS-Abenteuer", "Ein Cache im Wasser", "Ein Cache mit QR-Code",
        'A','H', CAT_GEOCACHING,
        "Richtig! Wherigo nutzt Cartridge-basierte Abenteuer.",
        "Falsch! Wherigo nutzt Cartridge-basierte Abenteuer."
    },
    {
        "Was ist ein Geocaching-HQ-Cache?",
        "Ein Cache im Besucherzentrum des HQ", "Ein Cache im Wald", "Ein Cache im Wasser",
        'A','L', CAT_GEOCACHING,
        "Richtig! HQ-Caches liegen im Besucherzentrum.",
        "Falsch! HQ-Caches liegen im Besucherzentrum."
    },
    {
        "Was ist ein GPS Adventure Maze?",
        "Eine GPS-Ausstellung", "Ein Virtual Cache", "Ein Mystery",
        'A','M', CAT_GEOCACHING,
        "Richtig! GPS Adventure Maze ist eine Ausstellung.",
        "Falsch! Es ist eine GPS-Ausstellung."
    },
    {
        "Was ist ein Adventure Lab?",
        "Ein app-basiertes Erlebnis ohne Dose", "Ein Multi-Cache", "Ein Virtual Reward",
        'A','M', CAT_GEOCACHING,
        "Richtig! Adventure Labs haben keine Dose.",
        "Falsch! Adventure Labs haben keine Dose."
    },
    {
        "Was ist ein Virtual Cache?",
        "Ein Cache ohne Dose", "Ein Cache mit Stempel", "Ein Cache im Wasser",
        'A','L', CAT_GEOCACHING,
        "Richtig! Virtuals haben keine Dose.",
        "Falsch! Virtuals haben keine Dose."
    },
    {
        "Was ist ein Webcam-Cache?",
        "Ein Cache, der ein Webcam-Foto erfordert", "Ein Cache mit QR-Code", "Ein Cache ohne Logbuch",
        'A','M', CAT_GEOCACHING,
        "Richtig! Webcam-Caches verlangen ein Webcam-Foto.",
        "Falsch! Webcam-Caches verlangen ein Webcam-Foto."
    },
    {
        "Was ist ein Project A.P.E. Cache?",
        "Ein Cache aus einer Filmkampagne", "Ein EarthCache", "Ein Virtual",
        'A','H', CAT_GEOCACHING,
        "Richtig! Project A.P.E. war eine Filmkampagne.",
        "Falsch! Project A.P.E. war eine Filmkampagne."
    },
    {
        "Wie viele der vierzehn Project A.P.E. Caches existieren heute noch?",
        "2", "14", "0",
        'A','H', CAT_GEOCACHING,
        "Richtig! Es existieren nur noch zwei.",
        "Falsch! Es existieren nur noch zwei."
    },
    {
        "Was ist ein Locationless Cache?",
        "Ein Cache ohne festen Ort", "Ein Cache im Ausland", "Ein Cache ohne Logbuch",
        'A','H', CAT_GEOCACHING,
        "Richtig! Locationless Caches haben keinen festen Ort.",
        "Falsch! Locationless Caches haben keinen festen Ort."
    },
    {
        "Was ist ein GIFF-Event?",
        "Ein Geocaching-Filmfestival", "Eine Geocaching-Fotoausstellung", "Eine Art Schrottwichteln",
        'A','M', CAT_GEOCACHING,
        "Richtig! GIFF ist ein Filmfestival.",
        "Falsch! GIFF ist ein Filmfestival."
    },
    {
        "Was ist ein Community Celebration Event (CCE)?",
        "Ein Jubiläums-Eventtyp", "Vortreffen vor einem CITO", "Tauschbörse für Mystery-Lösungen",
        'A','M', CAT_GEOCACHING,
        "Richtig! CCEs feiern Meilensteine.",
        "Falsch! CCEs feiern Meilensteine."
    },
    {
        "Was ist eine Geocaching Block Party?",
        "Feier eines Meilensteinjahrs", "Ein Mega-Event in Europa", "Ein Filmfestival",
        'A','H', CAT_GEOCACHING,
        "Richtig! Die Block Party fand am HQ statt.",
        "Falsch! Die Block Party fand am HQ statt."
    },
    {
        "Was ist ein 'Hider'?",
        "Der Verstecker eines Caches", "Der Finder eines Caches", "Der Reviewer",
        'A','L', CAT_GEOCACHING,
        "Richtig! Der Hider versteckt den Cache.",
        "Falsch! Der Hider ist der Verstecker."
    },
    {
        "Was macht ein Reviewer?",
        "Neue Listings prüfen", "Caches reparieren", "Events organisieren",
        'A','M', CAT_GEOCACHING,
        "Richtig! Reviewer prüfen neue Listings.",
        "Falsch! Reviewer prüfen neue Listings."
    },
    {
        "Was ist ein Trackable?",
        "Ein verfolgbares Objekt", "Ein Cachetyp", "Ein GPS-Gerät",
        'A','L', CAT_GEOCACHING,
        "Richtig! Trackables sind verfolgbar.",
        "Falsch! Trackables sind verfolgbar."
    },
    {
        "Was ist ein Geocoin?",
        "Eine sammelbare Metallmünze", "Währung im Geocaching-Shop", "Ein Referenzpunkt im Gelände",
        'A','L', CAT_GEOCACHING,
        "Richtig! Geocoins sind sammelbare Münzen.",
        "Falsch! Geocoins sind sammelbare Münzen."
    },
    {
        "Was bedeutet DNF?",
        "Did Not Find", "Do Not Follow", "Double No Find",
        'A','L', CAT_GEOCACHING,
        "Richtig! DNF bedeutet nicht gefunden.",
        "Falsch! DNF bedeutet Did Not Find."
    },
    {
        "Was bedeutet FTF?",
        "First To Find", "Fast Track Find", "Follow The Finder",
        'A','M', CAT_GEOCACHING,
        "Richtig! FTF bedeutet Erster Finder.",
        "Falsch! FTF bedeutet First To Find."
    },
    {
        "Was muss ein 'Hider' vor dem Veröffentlichen tun?",
        "Listing erstellen und Regeln beachten", "Reviewer bezahlen", "GPS registrieren",
        'A','M', CAT_GEOCACHING,
        "Richtig! Regeln und Listing sind Pflicht.",
        "Falsch! Der Hider muss Regeln und Listing beachten."
    },
    {
        "Was prüfen Reviewer vor der Freigabe?",
        "Regelkonformität", "Cachegröße", "Schwierigkeit",
        'A','H', CAT_GEOCACHING,
        "Richtig! Reviewer prüfen die Einhaltung der Regeln.",
        "Falsch! Reviewer prüfen die Regelkonformität."
    },
    {
        "Was bedeutet T5 bei der T-Wertung?",
        "Sehr anspruchsvolles Gelände", "Leichtes Gelände", "Nur im Winter machbar",
        'A','H', CAT_GEOCACHING,
        "Richtig! T5 bedeutet schweres Gelände.",
        "Falsch! T5 bedeutet schweres Gelände."
    },
    {
        "Was bedeutet D5 bei der D-Wertung?",
        "Sehr schwieriges Rätsel", "Sehr leichter Cache", "Nur für Profis logbar",
        'A','H', CAT_GEOCACHING,
        "Richtig! D5 bedeutet höchste Rätselschwierigkeit.",
        "Falsch! D5 bedeutet höchste Rätselschwierigkeit."
    },
    {
        "Was ist OpenCaching (OC)?",
        "Eine alternative Geocaching-Plattform", "Ein GPS-Standard", "Ein Cachetyp",
        'A','M', CAT_GEOCACHING,
        "Richtig! OC ist eine alternative Plattform.",
        "Falsch! OC ist eine alternative Plattform."
    },
    {
        "Welche Cachegröße entspricht 'Regular'?",
        "Etwa 1 Liter", "10 Liter", "0,1 Liter",
        'A','M', CAT_GEOCACHING,
        "Richtig! Regular entspricht etwa 1 Liter.",
        "Falsch! Regular entspricht etwa 1 Liter."
    },
    {
        "Was ist ein Nano-Cache?",
        "Ein extrem kleiner Cache", "Ein Cache im Wasser", "Ein Cache mit Rätsel",
        'A','L', CAT_GEOCACHING,
        "Richtig! Nanos sind winzig.",
        "Falsch! Nanos sind extrem klein."
    },
    {
        "Was ist ein Bonus-Cache?",
        "Ein zusätzlicher Cache nach Aufgaben", "Ein Cache ohne Behälter", "Belohnung für einen FTF",
        'A','M', CAT_GEOCACHING,
        "Richtig! Bonus-Caches ergänzen andere Caches.",
        "Falsch! Bonus-Caches ergänzen andere Caches."
    },
    {
        "Was ist ein HQ Celebration Event?",
        "Geocaching-Jubiläum in Seattle", "Event mit 500.000+ Teilnehmern", "Geburtstag des GPS",
        'A','M', CAT_GEOCACHING,
        "Richtig! HQ Celebrations feiern Meilensteine.",
        "Falsch! HQ Celebrations feiern Meilensteine."
    },
    {
        "Was ist GC43?",
        "Der älteste Cache Europas", "Der erste EarthCache", "Der erste Mystery",
        'A','H', CAT_GEOCACHING,
        "Richtig! GC43 ist Europas ältester Cache.",
        "Falsch! GC43 ist Europas ältester Cache."
    },
    {
        "Wo liegt GC40?",
        "Belgien", "Irland", "Deutschland",
        'A','H', CAT_GEOCACHING,
        "Richtig! GC40 liegt in Belgien.",
        "Falsch! GC40 liegt in Belgien."
    },
    {
        "Welcher Cache hatte lange die meisten Favoritenpunkte?",
        "Lego - einer ist zu viel", "Project APE", "Europe's First",
        'A','H', CAT_GEOCACHING,
        "Richtig! Der Lego-Cache hatte über 11.500 FP.",
        "Falsch! Es war der Lego-Cache."
    },
    {
        "Warum wurde GC13Y2Y archiviert?",
        "Beschädigte Giraffe", "Regelverstoß", "Reviewer hat sich verklickt",
        'A','H', CAT_GEOCACHING,
        "Richtig! Die Giraffe war beschädigt.",
        "Falsch! Die Giraffe war beschädigt."
    },
    {
        "Was ist ein Adventure Lab Bonus?",
        "Ein zusätzlicher Cache nach Abschluss eines Labs", "Ein Virtual", "Ein EarthCache",
        'A','M', CAT_GEOCACHING,
        "Richtig! Bonus-Caches ergänzen Adventure Labs.",
        "Falsch! Bonus-Caches ergänzen Adventure Labs."
    },
    {
        "Was war ursprünglich eine 'Block Party'?",
        "Ein Event-Cache am HQ", "Event in Kanada", "Vorläufer vom Oktoberfest",
        'A','M', CAT_GEOCACHING,
        "Richtig! Die Block Party war ein HQ-Event.",
        "Falsch! Die Block Party war ein HQ-Event."
    },
    {
        "Was ist ein Locationless Cache?",
        "Cache ohne feste Koordinaten", "Gemuggelter Cache", "Archivierter Cache",
        'A','H', CAT_GEOCACHING,
        "Richtig! Neue Locationless Caches sind Event-basiert.",
        "Falsch! Neue Locationless Caches sind Event-basiert."
    },
    {
        "Was ist ein Challenge Cache?",
        "Ein Cache mit Logbedingung", "Ein Tik-Tok-Phänomen", "Eine Diät für Geocacher",
        'A','H', CAT_GEOCACHING,
        "Richtig! Challenge Caches haben Logbedingungen.",
        "Falsch! Challenge Caches haben Logbedingungen."
    },
    {
        "Was ist ein Premium-Only Cache?",
        "Nur für Premium-Mitglieder sichtbar", "Nur für Reviewer sichtbar", "Nur bei Events sichtbar",
        'A','L', CAT_GEOCACHING,
        "Richtig! Premium-Only Caches sind nur für Premium-Mitglieder sichtbar.",
        "Falsch! Premium-Only Caches sind nur für Premium-Mitglieder sichtbar."
    },
    {
        "Welche Mindestabstandsregel gilt zwischen zwei Geocaches?",
        "161 Meter", "50 Meter", "500 Meter",
        'A','H', CAT_GEOCACHING,
        "Richtig! Die 161-Meter-Regel gilt weltweit.",
        "Falsch! Es sind 161 Meter."
    },
    {
        "Was bedeutet das Attribut 'Stealth Required'?",
        "Unauffälliges Verhalten nötig", "Nur nachts machbar", "Nur mit Werkzeug machbar",
        'A','M', CAT_GEOCACHING,
        "Richtig! Man soll unauffällig suchen.",
        "Falsch! Es bedeutet unauffälliges Verhalten."
    },
    {
        "Was bedeutet das Attribut 'Tiere vor Ort'?",
        "Es können Tiere anwesend sein", "Der Cache ist ein Tier", "Es ist ein Zoo-Cache",
        'A','L', CAT_GEOCACHING,
        "Richtig! Tiere können vor Ort sein.",
        "Falsch! Es bedeutet Tiere vor Ort."
    },
    {
        "Was bedeutet die D-Wertung?",
        "Schwierigkeit des Rätsels oder Verstecks", "Nur an Wochentagen mit 'D' verfügbar", "Cachegröße",
        'A','L', CAT_GEOCACHING,
        "Richtig! D steht für Difficulty.",
        "Falsch! D steht für Difficulty."
    },
    {
        "Was bedeutet die T-Wertung?",
        "Geländeschwierigkeit", "Rätselschwierigkeit", "Cachegröße",
        'A','L', CAT_GEOCACHING,
        "Richtig! T steht für Terrain.",
        "Falsch! T steht für Terrain."
    },
    {
        "Welche Kombination ist die schwierigste?",
        "D5/T5", "D1/T1", "D7/T7",
        'A','M', CAT_GEOCACHING,
        "Richtig! D5/T5 ist die höchste Schwierigkeit.",
        "Falsch! D5/T5 ist die höchste Schwierigkeit."
    },
    {
        "Was ist ein 'Needs Maintenance'-Log?",
        "Hinweis auf Probleme am Cache", "Hinweis auf FTF", "Hinweis auf Reviewer in der Nähe",
        'A','L', CAT_GEOCACHING,
        "Richtig! Es weist auf Probleme hin.",
        "Falsch! Es weist auf Probleme hin."
    },
    {
        "Was ist ein 'Needs Archived'-Log?",
        "Bitte um Archivierung", "Bitte um FTF", "Bitte um neue Dose",
        'A','H', CAT_GEOCACHING,
        "Richtig! Es fordert Archivierung an.",
        "Falsch! Es fordert Archivierung an."
    },
    {
        "Wer darf einen Cache archivieren?",
        "Reviewer oder HQ", "Jeder Finder", "Nur der Owner",
        'A','H', CAT_GEOCACHING,
        "Richtig! Reviewer oder HQ können archivieren.",
        "Falsch! Reviewer oder HQ archivieren."
    },
    {
        "Was ist ein 'Owner Maintenance'-Log?",
        "Der Owner bestätigt Wartung", "Der Owner löscht Logs", "Der Owner ändert Koordinaten",
        'A','L', CAT_GEOCACHING,
        "Richtig! Der Owner bestätigt Wartung.",
        "Falsch! Der Owner bestätigt Wartung."
    },
    {
        "Was ist ein 'Write Note'-Log?",
        "Ein neutraler Hinweis", "Ein Fundlog", "Ein DNF",
        'A','L', CAT_GEOCACHING,
        "Richtig! Es ist ein neutraler Hinweis.",
        "Falsch! Es ist ein neutraler Hinweis."
    },
    {
        "Was ist ein 'Watchlist'-Eintrag?",
        "Benachrichtigungen über Logs", "Ein Favoritenpunkt", "Ein Trackable",
        'A','M', CAT_GEOCACHING,
        "Richtig! Man erhält Log-Benachrichtigungen.",
        "Falsch! Es sind Log-Benachrichtigungen."
    },
    {
        "Was ist ein Favoritenpunkt?",
        "Auszeichnung für gute Caches", "Ein Trackable", "Ein Souvenir",
        'A','L', CAT_GEOCACHING,
        "Richtig! Favoritenpunkte zeichnen gute Caches aus.",
        "Falsch! Favoritenpunkte zeichnen gute Caches aus."
    },
    {
        "Wie erhält man Favoritenpunkte?",
        "Durch Funde als Premium-Mitglied", "Durch Rätsel lösen", "Durch Reviewer",
        'A','M', CAT_GEOCACHING,
        "Richtig! Premium-Mitglieder erhalten FP durch Funde.",
        "Falsch! Premium-Mitglieder erhalten FP durch Funde."
    },
    {
        "Was ist ein Souvenir?",
        "Digitale Auszeichnung", "Ein Trackable", "Ein Logbuch",
        'A','L', CAT_GEOCACHING,
        "Richtig! Souvenirs sind digitale Auszeichnungen.",
        "Falsch! Souvenirs sind digitale Auszeichnungen."
    },
    {
        "Wann erhält man Souvenirs?",
        "Bei bestimmten Aktionen oder Orten", "Bei jedem Fund", "Nur bei Events",
        'A','M', CAT_GEOCACHING,
        "Richtig! Souvenirs gibt es zu Aktionen oder Orten.",
        "Falsch! Souvenirs gibt es zu Aktionen oder Orten."
    },
    {
        "Was ist ein 'Jasmer-Challenge'?",
        "Finde Caches aus jedem Monat seit 2000", "Finde 1000 Caches", "Finde alle Cachetypen",
        'A','H', CAT_GEOCACHING,
        "Richtig! Jasmer verlangt Funde aus jedem Monat seit 2000.",
        "Falsch! Jasmer verlangt Funde aus jedem Monat seit 2000."
    },
    {
        "Was ist ein '365er Grid'?",
        "Jeden Kalendertag einen Fund", "365 Mysterys", "365 EarthCaches",
        'A','H', CAT_GEOCACHING,
        "Richtig! Es geht um tägliche Funde.",
        "Falsch! Es geht um tägliche Funde."
    },
    {
        "Was ist ein 'D/T-Matrix'-Grid?",
        "Alle 81 D/T-Kombinationen finden", "81 Mysterys lösen", "81 Events besuchen",
        'A','H', CAT_GEOCACHING,
        "Richtig! Es geht um alle 81 Kombinationen.",
        "Falsch! Es geht um alle 81 Kombinationen."
    },
    {
        "Was ist ein 'Powertrail'?",
        "Viele Caches in Serie", "Ein einzelner T5", "Ein Event",
        'A','L', CAT_GEOCACHING,
        "Richtig! Powertrails bestehen aus vielen Caches.",
        "Falsch! Powertrails bestehen aus vielen Caches."
    },
    {
        "Was ist eine 'Geoart'?",
        "Bild aus Caches auf der Karte", "Eine besondere Bergkette", "Eine Geocaching-Kunstausstellung",
        'A','M', CAT_GEOCACHING,
        "Richtig! Geoarts bilden Bilder auf der Karte.",
        "Falsch! Geoarts bilden Bilder auf der Karte."
    },
    {
        "Was ist ein 'FTF-Run'?",
        "Schnelles Losfahren nach Publish", "Ein Marathon", "Ein Event",
        'A','L', CAT_GEOCACHING,
        "Richtig! FTF-Runs sind schnelle Fahrten nach Publish.",
        "Falsch! Es ist ein schneller Start nach Publish."
    },
    {
        "Was ist eine 'Reviewer Note'?",
        "Nachricht an Reviewer", "Nachricht an Finder", "Nachricht an Owner",
        'A','M', CAT_GEOCACHING,
        "Richtig! Reviewer Notes sind für Reviewer.",
        "Falsch! Reviewer Notes sind für Reviewer."
    },
    {
        "Was ist ein 'Publish-Log'?",
        "Reviewer veröffentlicht Cache", "Owner archiviert Cache", "Finder loggt Cache",
        'A','L', CAT_GEOCACHING,
        "Richtig! Reviewer veröffentlichen Caches.",
        "Falsch! Reviewer veröffentlichen Caches."
    },
    {
        "Was ist ein 'Beta-Test' bei Caches?",
        "Vorab-Test durch andere Cacher", "Test durch Reviewer", "Test durch HQ",
        'A','M', CAT_GEOCACHING,
        "Richtig! Beta-Tester prüfen Caches vorab.",
        "Falsch! Beta-Tester prüfen Caches vorab."
    },
    {
        "Was ist ein 'Spoiler' im Geocaching?",
        "Information, die das Rätsel verrät", "Ein Trackable", "Ein Event",
        'A','L', CAT_GEOCACHING,
        "Richtig! Spoiler verraten Lösungen.",
        "Falsch! Spoiler verraten Lösungen."
    },
    {
        "Was ist ein 'Proxy' bei Geocoins?",
        "Ersatz für eine echte Coin", "Ein Virtual", "Ein Mystery",
        'A','M', CAT_GEOCACHING,
        "Richtig! Proxys ersetzen echte Coins.",
        "Falsch! Proxys ersetzen echte Coins."
    },
    {
        "Was ist ein 'Travel Bug Hotel'?",
        "Cache zum Tauschen von Trackables", "Ein Event", "Ein Mystery",
        'A','L', CAT_GEOCACHING,
        "Richtig! TB-Hotels dienen Trackables.",
        "Falsch! TB-Hotels dienen Trackables."
    },
    {
        "Was ist eine 'GeoTour'?",
        "Offizielle Serie thematischer Caches", "Ein Powertrail", "Ein Virtual",
        'A','M', CAT_GEOCACHING,
        "Richtig! GeoTours sind thematische Serien.",
        "Falsch! GeoTours sind thematische Serien."
    },
    {
        "Was ist ein 'Cache Owner'?",
        "Der Besitzer des Caches", "Der erste Finder", "Der Reviewer",
        'A','L', CAT_GEOCACHING,
        "Richtig! Der Owner besitzt den Cache.",
        "Falsch! Der Owner besitzt den Cache."
    },
    {
        "Was ist ein 'Cache Listing'?",
        "Die Beschreibung des Caches", "Das Logbuch", "Der Container",
        'A','L', CAT_GEOCACHING,
        "Richtig! Das Listing beschreibt den Cache.",
        "Falsch! Das Listing beschreibt den Cache."
    },
    {
        "Was ist ein 'Hint'?",
        "verschlüsselter Hinweis im Listing", "ein Trackable im Cache", "ein Logeintrag",
        'A','L', CAT_GEOCACHING,
        "Richtig! Hints sind verschlüsselte Hinweise.",
        "Falsch! Hints sind verschlüsselte Hinweise."
    },
    {
        "Was ist ein 'Cache Container'?",
        "der Behälter des Caches", "ein Ersatzlogbuch", "Versandbox für Trackables",
        'A','L', CAT_GEOCACHING,
        "Richtig! Der Container enthält das Logbuch.",
        "Falsch! Der Container enthält das Logbuch."
    },
    {
        "Was ist ein 'Logbuch'?",
        "Buch zum Eintragen für Finder", "Tagebuch eines Cachers", "Liste von Reviewer-Beanstandungen",
        'A','L', CAT_GEOCACHING,
        "Richtig! Das Logbuch dient zum Eintragen.",
        "Falsch! Das Logbuch dient zum Eintragen."
    },
    {
        "Was sind 'Cache-Attribute'?",
        "Zusatzinformationen im Listing", "Sammelobjekte", "Tauschgegenstände",
        'A','L', CAT_GEOCACHING,
        "Richtig! Attribute geben Zusatzinformationen.",
        "Falsch! Attribute geben Zusatzinformationen."
    },
    {
        "Was ist ein 'Reviewer Disable'?",
        "Temporäre Deaktivierung durch Reviewer", "Dauerhafte Deaktivierung durch Reviewer", "Cache-Veröffentlichung durch Reviewer",
        'A','M', CAT_GEOCACHING,
        "Richtig! Reviewer können Caches temporär deaktivieren.",
        "Falsch! Reviewer können Caches temporär deaktivieren."
    }
}; // Ende des Arrays mit 100 Fragen

#define NUM_QUIZ_QUESTIONS (sizeof(quiz_questions) / sizeof(quiz_question_t))

#endif // QUIZ_DATA_H
