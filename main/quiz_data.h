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
    CAT_TECHNIK
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
    { "Wie viele Kontinente gibt es?", "Fünf", "Sechs", "Sieben", 'C', 'M', CAT_ALLGEMEIN, "Richtig! Es gibt sieben Kontinente.", "Falsch! Es gibt sieben Kontinente." },
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
    { "Wie heißt der Zauberschüler in Hogwarts?", "Harry Potter", "Ron Weasley", "Neville Longbottom", 'A', 'L', CAT_FILM, "Richtig! Harry Potter ist der Zauberschüler.", "Falsch! Harry Potter ist der Zauberschüler." },
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
}; // Ende des Arrays mit 100 Fragen

#define NUM_QUIZ_QUESTIONS (sizeof(quiz_questions) / sizeof(quiz_question_t))

#endif // QUIZ_DATA_H
