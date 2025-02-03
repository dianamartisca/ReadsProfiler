CREATE TABLE clients (
	client_id INTEGER UNIQUE,
	name TEXT
);

CREATE TABLE books (
    book_id INTEGER UNIQUE,
    book_title TEXT,
    author_id INTEGER,
    isbn TEXT UNIQUE,
    year INTEGER,
    rating FLOAT,
    book TEXT
);

CREATE TABLE authors (
    author_id INTEGER UNIQUE,
    name TEXT
);

CREATE TABLE genres (
    genre_id INTEGER UNIQUE,
    name TEXT,
    parent_id INTEGER 
);

CREATE TABLE books_genres (
	genre_id INTEGER,
	book_id INTEGER
);

CREATE TABLE authors_genres (
	genre_id INTEGER,
	author_id INTEGER
);

CREATE TABLE search_history (
    search_id INTEGER UNIQUE,
    client_id INTEGER,
    search_text TEXT,
    accessed_books TEXT, 
    downloaded_book_id INTEGER 
);

CREATE TABLE rating_history (
    client_id INTEGER,
    book_id INTEGER,
    rating INTEGER
);

INSERT INTO genres VALUES (1, 'ficțiune', NULL);
INSERT INTO genres VALUES (2, 'poezie', NULL);
INSERT INTO genres VALUES (3, 'dramă', NULL);
INSERT INTO genres VALUES (4, 'non-ficțiune', NULL);

INSERT INTO genres VALUES (5, 'acțiune', 1);
INSERT INTO genres VALUES (6, 'aventură', 1);
INSERT INTO genres VALUES (7, 'romance', 1);
INSERT INTO genres VALUES (8, 'science-fiction', 1);
INSERT INTO genres VALUES (9, 'thriller', 1);
INSERT INTO genres VALUES (10, 'mister', 1);
INSERT INTO genres VALUES (11, 'istoric', 1);
INSERT INTO genres VALUES (12, 'război', 1);
INSERT INTO genres VALUES (13, 'roman', 1);
INSERT INTO genres VALUES (14, 'basm', 1);

INSERT INTO genres VALUES (15, 'artă poetică', 2);
INSERT INTO genres VALUES (16, 'poem', 2);
INSERT INTO genres VALUES (17, 'pastel', 2);
INSERT INTO genres VALUES (18, 'elegie', 2);
INSERT INTO genres VALUES (19, 'romanță', 2);

INSERT INTO genres VALUES (20, 'comedie', 3);
INSERT INTO genres VALUES (21, 'tragedie', 3);

INSERT INTO genres VALUES (22, 'biografie', 4);
INSERT INTO genres VALUES (23, 'psihologie', 4);
INSERT INTO genres VALUES (24, 'filosofie', 4);
INSERT INTO genres VALUES (25, 'dezvoltare personală', 4);
INSERT INTO genres VALUES (26, 'istorie', 4);
INSERT INTO genres VALUES (27, 'jurnal', 4);

INSERT INTO books VALUES (50, 'Poesii', 51, '9789739013178', 1883, 8, 'Cu perdelele lăsate/ Șed la masa mea de brad,/ Focul pălpăe în sobă,/ Iară eu pe gănduri cad.');
INSERT INTO authors VALUES (51, 'Mihai Eminescu');
INSERT INTO books_genres VALUES (2, 50);
INSERT INTO books_genres VALUES (15, 50);
INSERT INTO books_genres VALUES (18, 50);
INSERT INTO books_genres VALUES (19, 50);
INSERT INTO authors_genres VALUES (2, 51);
INSERT INTO authors_genres VALUES (15, 51);
INSERT INTO authors_genres VALUES (18, 51);
INSERT INTO authors_genres VALUES (19, 51);

INSERT INTO books VALUES (52, 'O scrisoare pierdută', 53, '9789732332153', 1884, 9.3, '(O anticameră bine mobilată. Uşă în fund cu două ferestre mari de laturi. La dreapta, în planul din fund o uşă, la stânga altă uşă, în planul din faţă. În stânga, planul întâi, canapea şi un fotoliu)');
INSERT INTO authors VALUES (53, 'Ion Luca Caragiale');
INSERT INTO books_genres VALUES (3, 52);
INSERT INTO books_genres VALUES (20, 52);
INSERT INTO authors_genres VALUES (3, 53);
INSERT INTO authors_genres VALUES (20, 53);

INSERT INTO books VALUES (54, 'Amintiri din copilărie', 55, '9781456531621', 1892, 9, 'STAU CÂTEODATĂ ŞI-MI ADUC AMINTE CE VREMI şi ce oameni mai erau în părţile noastre pe când începusem şi eu, drăgăliţă-Doamne, a mă ridica băieţaş la casa părinţilor mei');
INSERT INTO authors VALUES (55, 'Ion Creangă');
INSERT INTO books_genres VALUES (1, 54);
INSERT INTO books_genres VALUES (5, 54);
INSERT INTO books_genres VALUES (13, 54);
INSERT INTO authors_genres VALUES (1, 55);
INSERT INTO authors_genres VALUES (5, 55);
INSERT INTO authors_genres VALUES (13, 55);

INSERT INTO books VALUES (56, 'Zodia Cancerului sau vremea Ducăi-Vodă', 57, '9789735910334', 1929, 7.8, 'ÎN CARE SE VEDE CUM INTRĂ ÎN MOLDOVA UN CĂLĂTOR DINTR-O ŢARĂ DEPĂRTATĂ ŞI CUM ILIE TURCULEŢ NU-I NUMAI CĂPITAN DE STEAG, CI ŞI CETITOR DE STELE. Era la sfîrşitul lunii septemvrie care, în Moldova, se chiamă brumărel, anul nou de la zidirea lumii 7188, iar de la Hristos 1679.');
INSERT INTO authors VALUES (57, 'Mihail Sadoveanu');
INSERT INTO books_genres VALUES (1, 56);
INSERT INTO books_genres VALUES (11, 56);
INSERT INTO books_genres VALUES (13, 56);
INSERT INTO authors_genres VALUES (1, 57);
INSERT INTO authors_genres VALUES (11, 57);
INSERT INTO authors_genres VALUES (13, 57);

INSERT INTO books VALUES (58, 'Fire de tort', 59, '9786064607393', 1896, 7.5, 'Zările, de farmec pline,/ Strălucesc în luminiș;/ Zboară mierlele-n tufiș/ Și din codri noaptea vine/ Pe furiș.');
INSERT INTO authors VALUES (59, 'George Coșbuc');
INSERT INTO books_genres VALUES (2, 58);
INSERT INTO books_genres VALUES (15, 58);
INSERT INTO books_genres VALUES (17, 58);
INSERT INTO authors_genres VALUES (2, 59);
INSERT INTO authors_genres VALUES (15, 59);
INSERT INTO authors_genres VALUES (17, 59);

INSERT INTO books VALUES (60, 'Crima lui Sylvestre Bonnard', 60, '9789735916138', 1881, 7.8, 'Am tras papucii în picioare şi mi-am pus halatul. Am şters lacrima cu care crivățul, suflind pe chei, îmi împăienjenise privirea. Un foc vesel ardea în soba camerei mele de lucru.');
INSERT INTO authors VALUES (61, 'Anatole France');
INSERT INTO books_genres VALUES (1, 60);
INSERT INTO books_genres VALUES (13, 60);
INSERT INTO authors_genres VALUES (1, 61);
INSERT INTO authors_genres VALUES (13, 61);

INSERT INTO books VALUES (62, 'Copilăria', 63, '9789734639908', 1914, 8.3, 'În odaia strâmtă şi întunecată, lângă fereastră, tata zace pe podea îmbrăcat în alb şi parcă nespus de lung. E desculţ şi degetele de la picioare i-s răşchirate în chip ciudat, iar cele de la mâinile care m-au mângâiat odinioară, aşezate acum cu smerenie pe piept, sunt şi ele chircite.');
INSERT INTO authors VALUES (63, 'Maxim Gorki');
INSERT INTO books_genres VALUES (1, 62);
INSERT INTO books_genres VALUES (13, 62);
INSERT INTO authors_genres VALUES (1, 63);
INSERT INTO authors_genres VALUES (13, 63);

INSERT INTO books VALUES (64, 'Pe drumuri de munte', 65, '9786066003261', 1912, 8.5, 'Orice călătorie, afară de cea pe jos, e după mine o călătorie pe picioare străine; a avea la îndemână cupeaua unui tren, roatele unei trăsuri sau picioarele unui cal înseamnă a merge șezând și a vedea numai ceea ce ți se dă, nu însă și tot ce ai voi.');
INSERT INTO authors VALUES (65, 'Calistrat Hogaș');
INSERT INTO books_genres VALUES (4, 64);
INSERT INTO books_genres VALUES (22, 64);
INSERT INTO authors_genres VALUES (4, 65);
INSERT INTO authors_genres VALUES (22, 65);

INSERT INTO books VALUES (66, 'Desculț', 67, '9786064609649', 1948, 7.1, '— Tudoreee… Deschide poarta!… Pe tata îl cheamă Tudor. Dar el rareori se află acasă. Cum auzeam strigând, săream la poartă.');
INSERT INTO authors VALUES (67, 'Zaharia Stancu');
INSERT INTO books_genres VALUES (4, 66);
INSERT INTO books_genres VALUES (22, 66);
INSERT INTO authors_genres VALUES (4, 67);
INSERT INTO authors_genres VALUES (22, 67);

INSERT INTO books VALUES (68, 'Moara cu noroc', 69, '9786069830802', 1881, 8.6, '— Omul să fie mulţumit cu sărăcia sa, căci, dacă e vorba, nu bogăţia, ci liniştea colibei tale te face fericit. Dar voi să faceţi după cum vă trage inima, şi Dumnezeu să vă ajute şi să vă acopere cu aripa bunătăţii sale.');
INSERT INTO authors VALUES (69, 'Ioan Slavici');
INSERT INTO books_genres VALUES (1, 68);
INSERT INTO books_genres VALUES (5, 68);
INSERT INTO authors_genres VALUES (1, 69);
INSERT INTO authors_genres VALUES (5, 69);

INSERT INTO books VALUES (70, 'Răscoala', 71, '9786067820133', 1932, 8, 'În aceeaşi Duminecă, pela amiazi, Grigore Iuga cu Titu Herdelea coborau în gara Burdea unde îi aştepta brişcă galbenă dela Amara cu Ichim pe capră.');
INSERT INTO authors VALUES (71, 'Liviu Rebreanu');
INSERT INTO books_genres VALUES (1, 70);
INSERT INTO books_genres VALUES (12, 70);
INSERT INTO books_genres VALUES (13, 70);
INSERT INTO authors_genres VALUES (1, 71);
INSERT INTO authors_genres VALUES (12, 71);
INSERT INTO authors_genres VALUES (13, 71);

INSERT INTO books VALUES (72, 'Moromeții', 73, '9786069098103', 1955, 9.2, 'Era începutul verii. Familia Moromete se întorsese mai devreme de la câmp. Cât ajunseseră acasă, Paraschi, cel mai mare dintre copii se dăduse jos din căruţă, lăsase pe alţii să deshame şi să dea jos uneltele, iar el întinsese pe prispă o haină veche şi se culcase peste ea gemând.');
INSERT INTO authors VALUES (73, 'Marin Preda');
INSERT INTO books_genres VALUES (1, 72);
INSERT INTO books_genres VALUES (5, 72);
INSERT INTO books_genres VALUES (6, 72);
INSERT INTO books_genres VALUES (13, 72);
INSERT INTO authors_genres VALUES (1, 73);
INSERT INTO authors_genres VALUES (5, 73);
INSERT INTO authors_genres VALUES (6, 73);
INSERT INTO authors_genres VALUES (13, 73);

INSERT INTO books VALUES (74, 'Călătorie prin Portugalia', 75, '9786303440590', 1981, 7.3, 'La porţile oraşului Bragança începe să plouă. Aşa e vremea, se rostogolesc pe cer nori mari şi întunecaţi, îţi pare că lumea, pentru a copia satele, s-­‐a acoperit cu ardezie, dar a îmbinat prost plăcile, fiindcă ploaia cade printre găuri şi călătorul e nevoit să se refugieze la Muzeul Abatelui de Baçal.');
INSERT INTO authors VALUES (75, 'Jose Saramago');
INSERT INTO books_genres VALUES (4, 74);
INSERT INTO books_genres VALUES (22, 74);
INSERT INTO books_genres VALUES (27, 74);
INSERT INTO authors_genres VALUES (4, 75);
INSERT INTO authors_genres VALUES (22, 75);
INSERT INTO authors_genres VALUES (27, 75);

INSERT INTO books VALUES (76, 'Jurnal', 77, '9786064024381', 1923, 8.4, 'Privitorii încremenesc când trenul le trece prin faţă. „Dacă el mă tot întreabă mereu.“ Sunetul „ea“ din „întreabă“, desprins de fraza rostită, a zburat departe ca o minge pe pajişte.');
INSERT INTO authors VALUES (77, 'Franz Kafka');
INSERT INTO books_genres VALUES (4, 76);
INSERT INTO books_genres VALUES (22, 76);
INSERT INTO books_genres VALUES (27, 76);
INSERT INTO authors_genres VALUES (4, 77);
INSERT INTO authors_genres VALUES (22, 77);
INSERT INTO authors_genres VALUES (27, 77);

INSERT INTO books VALUES (78, 'Șapte ani în Tibet', 79, '9786303440323', 2013, 8.5, 'Expediția noastră de explorare luase sfârşit la finele lui august 1939. Găsiserăm o nouă cale de acces si aşteptam la Karachi cargobotul care urma să ne ducă înapoi în Europa.');
INSERT INTO authors VALUES (79, 'Heinrich Harrer');
INSERT INTO books_genres VALUES (4, 78);
INSERT INTO books_genres VALUES (22, 78);
INSERT INTO books_genres VALUES (27, 78);
INSERT INTO authors_genres VALUES (4, 79);
INSERT INTO authors_genres VALUES (22, 79);
INSERT INTO authors_genres VALUES (27, 79);

INSERT INTO books VALUES (80, 'Focul', 81, '9782346135516', 1916, 8.7, 'Lucrarea își propune să schițeze două momente relevante ale dialogului dintre cultura română și cea franceză: receptarea scriitorilor francezi ai războiului în România anilor 1916-1926 și dialogul dintre culturile celor două țări aliate, în timpul războiului.');
INSERT INTO authors VALUES (81, 'Henri Barbusse');
INSERT INTO books_genres VALUES (1, 80);
INSERT INTO books_genres VALUES (11, 80);
INSERT INTO books_genres VALUES (12, 80);
INSERT INTO books_genres VALUES (13, 80);
INSERT INTO authors_genres VALUES (1, 81);
INSERT INTO authors_genres VALUES (11, 81);
INSERT INTO authors_genres VALUES (12, 81);
INSERT INTO authors_genres VALUES (13, 81);

INSERT INTO books VALUES (82, 'Generația canibală', 83, '9786303440828', 2024, 8.3, 'Anii ’90. Cad regimurile comuniste în tot blocul estic, URSS se dizolvă şi sălbaticii copii dingo pleacă în toate direcţiile plini de speranţă, entuziasm şi o poftă nebună de viaţă.');
INSERT INTO authors VALUES (83, 'Vasile Ernu');
INSERT INTO books_genres VALUES (4, 82);
INSERT INTO books_genres VALUES (22, 82);
INSERT INTO books_genres VALUES (27, 82);
INSERT INTO authors_genres VALUES (4, 83);
INSERT INTO authors_genres VALUES (22, 83);
INSERT INTO authors_genres VALUES (27, 83);

INSERT INTO books VALUES (84, 'Am fost actor', 85, '9786066397230', 2024, 9, 'Mă întreb pentru ce și pentru cine am scris această carte? Nu-mi pot ascunde mica vanitate, aceea care te face să scrijelești coaja copacilor cu numele tău, așa cum alții au scrijelit pereții închisorilor.');
INSERT INTO authors VALUES (85, 'Florin Zamfirescu');
INSERT INTO books_genres VALUES (4, 84);
INSERT INTO books_genres VALUES (22, 84);
INSERT INTO books_genres VALUES (27, 84);
INSERT INTO authors_genres VALUES (4, 85);
INSERT INTO authors_genres VALUES (22, 85);
INSERT INTO authors_genres VALUES (27, 85);

INSERT INTO books VALUES (86, 'Constantin Tănase. Un om serios', 87, '9786303440910', 2024, 7, 'Revista e un spectacol pentru toata lumea, de asta o iubesc. Nu trebuie sa fii cult si sensibil ca sa o pricepi sau sa ai scoli inalte. Imi place limbajul ei simplu si direct.');
INSERT INTO authors VALUES (87, 'Dorina Rusu');
INSERT INTO books_genres VALUES (4, 86);
INSERT INTO books_genres VALUES (22, 86);
INSERT INTO authors_genres VALUES (4, 87);
INSERT INTO authors_genres VALUES (22, 87);

INSERT INTO books VALUES (88, 'Testamentul din strada Nisipuri', 89, '9786303330518', 2019, 7.5, 'Mă şterg la ochi şi intru-in librărie,/ Nu-am bani să-ating o carte cu privirea,/ Nevinovat, mă trag spre-afară, fie/ Chiar din oraş, să-mi caut izbăvirea');
INSERT INTO authors VALUES (89, 'Șerban Codrin');
INSERT INTO books_genres VALUES (2, 88);
INSERT INTO authors_genres VALUES (2, 89);

INSERT INTO books VALUES (90, 'Numele tău', 91, '9789975868037', 1968, 9, 'Mami,/ tu ești Patria mea!/ Creștetul tău -/ vârful muntelui/ acoperit de nea');
INSERT INTO authors VALUES (91, 'Grigore Vieru');
INSERT INTO books_genres VALUES (2, 90);
INSERT INTO authors_genres VALUES (2, 91);

INSERT INTO books VALUES (92, 'Primele versuri', 93, '9786306543571', 2024, 8.7, 'Două manuscrise necunoscute, cu numeroase versuri inedite și variante timpurii scrise de Ion Pillat între 1905-1912, au ieșit la iveală în ultimii trei ani, într-un mod aproape miraculos.');
INSERT INTO authors VALUES (93, 'Ion Pillat');
INSERT INTO books_genres VALUES (2, 92);
INSERT INTO authors_genres VALUES (2, 93);

INSERT INTO books VALUES (94, 'Poezii', 95, '9789975367851', 2024, 8.5, 'Alexei Mateevici este poetul-simbol al Basarabiei. Nimeni de la noi nu a adunat atâta glorie (nu numai literară…) cu o singură poezie!');
INSERT INTO authors VALUES (95, 'Alexei Mateevici');
INSERT INTO books_genres VALUES (2, 94);
INSERT INTO authors_genres VALUES (2, 95);

INSERT INTO books VALUES (96, 'Enigma Otiliei', 97, '9786063350658', 1938, 9.1, 'Într-o seară de la începutul lui iulie 1909, cu puțin înainte de orele zece, un tânăr de vreo optsprezece ani, îmbrăcat în uniformă de licean [...]');
INSERT INTO authors VALUES (97, 'George Călinescu');
INSERT INTO books_genres VALUES (1, 96);
INSERT INTO books_genres VALUES (5, 96);
INSERT INTO books_genres VALUES (7, 96);
INSERT INTO books_genres VALUES (13, 96);
INSERT INTO authors_genres VALUES (1, 97);
INSERT INTO authors_genres VALUES (5, 97);
INSERT INTO authors_genres VALUES (7, 97);
INSERT INTO authors_genres VALUES (13, 97);

INSERT INTO books VALUES (98, 'Cartea cu jucării', 99, '9786068391434', 1931, 9, 'Pe vremea din poveste, stăpânii puteau să scurteze viaţa cui pofteau, cu nejudecată, pentru că nicio judecată nu era mai dreaptă decât a lor.');
INSERT INTO authors VALUES (99, 'Tudor Arghezi');
INSERT INTO books_genres VALUES (1, 98);
INSERT INTO books_genres VALUES (5, 98);
INSERT INTO authors_genres VALUES (1, 99);
INSERT INTO authors_genres VALUES (5, 99);

INSERT INTO books VALUES (100, 'Ultima noapte de dragoste, întâia noapte de război', 100, '9786068391076', 1931, 9, 'Pe vremea din poveste, stăpânii puteau să scurteze viaţa cui pofteau, cu nejudecată, pentru că nicio judecată nu era mai dreaptă decât a lor.');
INSERT INTO authors VALUES (101, 'Camil Petrescu');
INSERT INTO books_genres VALUES (1, 100);
INSERT INTO books_genres VALUES (5, 100);
INSERT INTO books_genres VALUES (7, 100);
INSERT INTO books_genres VALUES (12, 100);
INSERT INTO books_genres VALUES (13, 100);
INSERT INTO authors_genres VALUES (1, 101);
INSERT INTO authors_genres VALUES (5, 101);
INSERT INTO authors_genres VALUES (7, 101);
INSERT INTO authors_genres VALUES (12, 101);
INSERT INTO authors_genres VALUES (13, 101);

INSERT INTO books VALUES (102, 'Balade și idile', 59, '9786067820072', 1893, 8.7, 'Zările, de farmec pline,/ Strălucesc în luminiş;/ Zboară mierlele-n tufiş/ Şi din codri noaptea vine/ Pe furiş.');
INSERT INTO books_genres VALUES (2, 102); 
INSERT INTO books_genres VALUES (15, 102);
INSERT INTO books_genres VALUES (17, 102);

INSERT INTO books VALUES (104, 'Cântec de iubire', 91, '9786067226409', 2024, 8.9, 'Cartea de față adună într-o imagine sintetică întreaga creaţie literară a lui Grigore Vieru, definit memorabil de criticul Eugen Simion ca un „poet cu lira-n lacrimi”: poezia lirică, poezia pentru copii şi poemele aforistice...');
INSERT INTO books_genres VALUES (2, 104);
INSERT INTO books_genres VALUES (15, 104);
INSERT INTO books_genres VALUES (16, 104);
INSERT INTO authors_genres VALUES (15, 91); 
INSERT INTO authors_genres VALUES (16, 91); 

INSERT INTO books VALUES (106, 'Versuri alese', 99, '9786068391458', 1946, 8.8, 'Nu-ți voi lăsa drept bunuri, după moarte,/ Decât un nume adunat pe o carte');
INSERT INTO books_genres VALUES (2, 106); 
INSERT INTO books_genres VALUES (15, 106);
INSERT INTO books_genres VALUES (17, 106);
INSERT INTO books_genres VALUES (18, 106);
INSERT INTO authors_genres VALUES (2, 99); 
INSERT INTO authors_genres VALUES (15, 99); 
INSERT INTO authors_genres VALUES (17, 99); 
INSERT INTO authors_genres VALUES (18, 99); 

INSERT INTO books VALUES (108, 'Cele șapte neveste ale lui Barbă-Albastră și alte povești minunate', 61, '9786060232629', 1992, 7.9, 'Domnul Froidefond este sărac cu duhul și are suflet curat. Trăiește catalogal. Cunoaște titlul și formatul fiecăruia dintre volumele care împodobesc acești pereți, posedând astfel singura știință exactă pe care ți-o poți însuși într-o bibliotecă și, deoarece n-a pătruns nicicând în miezul unei cărți, a fost ferit de flasca incertitudine, de eroarea cu o sută de guri, de cumplita îndoială, monștri pe care-i zămislește lectura într-o minte fecundă.');
INSERT INTO books_genres VALUES (1, 108);
INSERT INTO books_genres VALUES (5, 108);
INSERT INTO authors_genres VALUES (5, 61);

INSERT INTO books VALUES (110, 'Teatru - Liviu Rebreanu', 71, '9789731898551', 2020, 7.7, 'Daca romanele sunt cea mai inalta forma de relief a operei lui Liviu Rebreanu, teatrul constituie in viata lui o preocupare statornica si care i-a absorbit o buna parte a zilelor.');
INSERT INTO books_genres VALUES (3, 110);
INSERT INTO authors_genres VALUES (3, 71);

INSERT INTO books VALUES (112, 'Pădurea spânzuraților', 71, '9786063389733', 1922, 8.1, 'Sub cerul cenușiu de toamnă ca un clopot uriaș de sticlă aburită, spânzurătoarea nouă și sfidătoare, înfiptă la marginea satului, întindea brațul cu ștreangul spre câmpia neagră');
INSERT INTO books_genres VALUES (1, 112);
INSERT INTO books_genres VALUES (5, 112);
INSERT INTO books_genres VALUES (12, 112);
INSERT INTO authors_genres VALUES (5, 71);

INSERT INTO books VALUES (114, 'Povestea lui Harap-Alb', 55, '9786068391069', 1877, 8.9, 'Amu cică era odată într-o ţară un crai, care avea trei feciori. Şi craiul acela mai avea un frate mai mare, care era împărat într-o altă ţară, mai depărtată.');
INSERT INTO books_genres VALUES (1, 114);
INSERT INTO books_genres VALUES (14, 114);
INSERT INTO authors_genres VALUES (14, 55);

INSERT INTO books VALUES (116, 'Sălbaticii copii Dingo', 83, '9789734685370', 2021, 9.3, 'Anii ’80. Patru prieteni se întîlnesc în gara din Chişinău. Vor pleca împreună în vacanţă în Crimeea, la mare. Sînt lipsiţi de griji, nu au de unde să ştie că fac parte din generaţia ultimilor copii sovietici.');
INSERT INTO books_genres VALUES (4, 116);
INSERT INTO books_genres VALUES (22, 116);
INSERT INTO books_genres VALUES (27, 116);

INSERT INTO books VALUES (118, 'Pe Argeș în sus', 93, '9786064614377', 2021, 9.5, 'Acolo unde-n Argeş se varsă Râul Doamnei/ Şi murmură pe ape copilăria mea');
INSERT INTO books_genres VALUES (2, 118);
INSERT INTO books_genres VALUES (15, 118);
INSERT INTO books_genres VALUES (17, 118);
INSERT INTO authors_genres VALUES (15, 93);
INSERT INTO authors_genres VALUES (17, 93);

INSERT INTO books VALUES (120, 'Nuvele și povestiri', 53, '9786067935776', 2019, 9.6, 'Era odata la Bagdad, sub domnia strălucitului calif Harun-al-Raşid, un negutător bogat, care avea o nevastă bătrână şi un fecior, Abu-Hasan, crescut până la vreo treizeci de ani strâns de aproape în toate privintele.');
INSERT INTO books_genres VALUES (1, 120);
INSERT INTO books_genres VALUES (5, 120);
INSERT INTO authors_genres VALUES (1, 53);
INSERT INTO authors_genres VALUES (5, 53);

INSERT INTO books VALUES (122, 'Cain', 75, '9789734647958', 2014, 9.3, 'Dupa ce-si ucide fratele intr-un moment de frustrare, Cain ajunge la o intelegere cu Dumnezeu si scapa cu viata, condamnat la vesnica pribegie, cu un sac de merinde si avind drept tovaras un magar.');
INSERT INTO books_genres VALUES (1, 122);
INSERT INTO books_genres VALUES (11, 122);
INSERT INTO books_genres VALUES (13, 122);
INSERT INTO authors_genres VALUES (1, 75);
INSERT INTO authors_genres VALUES (11, 75);
INSERT INTO authors_genres VALUES (13, 75);

INSERT INTO books VALUES (124, 'Călin Nebunul', 51, '9789975749626', 1968, 8.3, 'Era odat-un împărat ș-avea trei fete și erau așa de frumoase, de la soare te puteai uita, da la dânsele ba. Acu, cele două erau cum erau, da cea mijlocie nici se mai povestește frumusețea ei.');
INSERT INTO books_genres VALUES (1, 124);
INSERT INTO books_genres VALUES (14, 124);
INSERT INTO books_genres VALUES (6, 124);
INSERT INTO authors_genres VALUES (1, 51);
INSERT INTO authors_genres VALUES (14, 51);
INSERT INTO authors_genres VALUES (6, 51);

INSERT INTO books VALUES (126, 'Mara', 69, '9786060910596', 1894, 8.8, 'A rămas Mara, săraca, văduvă cu doi copii, sărăcuții de ei, dar era tânără, și voinică, și harnică, și Dumnezeu a mai lăsat să aibă și noroc.');
INSERT INTO books_genres VALUES (1, 126);
INSERT INTO books_genres VALUES (6, 126);
INSERT INTO authors_genres VALUES (6, 69);

INSERT INTO books VALUES (128, 'Baltagul', 57, '9786069335505', 1930, 8.9, 'Domnul Dumnezeu, după ce a alcătuit lumea, a pus rânduială şi semn fiecărui neam. Pe ţigan l-a învăţat să cânte cu cetera şi neamţului i-a dat şurubul.');
INSERT INTO books_genres VALUES (1, 128);
INSERT INTO books_genres VALUES (5, 128);
INSERT INTO books_genres VALUES (10, 128);
INSERT INTO authors_genres VALUES (5, 57);
INSERT INTO authors_genres VALUES (10, 57);

INSERT INTO books VALUES (130, 'Iarna pe uliță', 59, '9786303216614', 1896, 9.8, 'A-nceput de ieri să cadă/ Câte-un fulg, acum a stat,/ Norii s-au mai răzbunat/ Spre apus, dar stau grămadă/ Peste sat..');
INSERT INTO books_genres VALUES (2, 130);
INSERT INTO books_genres VALUES (17, 130);

INSERT INTO books VALUES (132, 'O noapte furtunoasă', 53, '9786069830826', 1879, 9.9, 'Jupân Dumitrache: (urmând o vorbă începută) Iaca, niște papugii... niște scârța-scârța pe hârtie! Ii știm noi! Mănâncă pe datorie, bea pe veresie, trag lumea pe sfoară cu pișicherlicuri... ');
INSERT INTO books_genres VALUES (3, 132);
INSERT INTO books_genres VALUES (20, 132);

INSERT INTO books VALUES (134, 'Mama', 63, '9789734674138', 2018, 8.5, 'Eu ştiu, va fi o vreme cînd oamenii vor avea admiraţie unul pentru altul, cînd fiecare va fi ca o stea în faţa celorlalţi! Vor fi pe pămînt oameni liberi, măreţi prin libertatea lor, toţi vor merge cu sufletul deschis, nici o inimă nu va mai şti ce e invidia, nimeni nu va mai şti ce e răutatea.');
INSERT INTO books_genres VALUES (1, 134);
INSERT INTO books_genres VALUES (13, 134);

INSERT INTO books VALUES (136, 'Cel mai iubit dintre pământeni', 73, '9786069098158', 1980, 8.9, 'Moartea e un fenomen simplu în natură, numai oamenii îl fac înspăimîntător. Vorbesc de moartea naturală, care adesea e o dulce ispită.');
INSERT INTO books_genres VALUES (1, 136);
INSERT INTO books_genres VALUES (5, 136);
INSERT INTO books_genres VALUES (13, 136);

INSERT INTO books VALUES (138, 'Viața ca o pradă', 73, '9789737883988', 1977, 8.5, 'Aventura conştiinţei mele a început într-o zi de iarnă când o anumită întâmplare m-a făcut să înţeleg deodată că exist. Era multă lume în casă, fiinţe mari, aşezate în cerc pe scaune mici şi care se uitau la mine cu priviri de recunoaştere, dar parcă îmi spuneau cu ostilitate, te vedem, eşti de-al nostru, dar ce faci?');
INSERT INTO books_genres VALUES (4, 138);
INSERT INTO books_genres VALUES (22, 138);
INSERT INTO books_genres VALUES (23, 138);
INSERT INTO books_genres VALUES (24, 138);
INSERT INTO authors_genres VALUES (4, 73);
INSERT INTO authors_genres VALUES (22, 73);
INSERT INTO authors_genres VALUES (23, 73);
INSERT INTO authors_genres VALUES (24, 73);

INSERT INTO books VALUES (140, 'Cartea nunții', 97, '9786306538171', 1933, 8.2, 'Când salcâmii stației începură să alunece pe dinaintea trenului, lovind ușor cu frunzișul streașina vagonului, Jim trase ușa compartimentului și merse să se așeze la locul său de lângă fereastră.');
INSERT INTO books_genres VALUES (1, 140);
INSERT INTO books_genres VALUES (7, 140);
INSERT INTO books_genres VALUES (13, 140);

INSERT INTO books VALUES (142, 'Istoria literaturii române', 97, '9786060911647', 1941, 8.8, 'Volumul de față este o mică Istorie a literaturii române pe care o anunțam în prefața ediției celei mari, ca urmând a apare aproape numaidecât după aceea.');
INSERT INTO books_genres VALUES (4, 142);
INSERT INTO books_genres VALUES (26, 142);
INSERT INTO authors_genres VALUES (4, 97);
INSERT INTO authors_genres VALUES (26, 97);

INSERT INTO books VALUES (144, 'Metamorfoza', 77, '9786069604045', 1915, 8.9, 'Într-o bună dimineaţă, cînd Gregor Samsa se trezi în patul lui, după o noapte de vise zbuciumate, se pomeni metamorfozat într-o gînganie înspăimîntătoare.');
INSERT INTO books_genres VALUES (1, 144);
INSERT INTO books_genres VALUES (5, 144);
INSERT INTO authors_genres VALUES (1, 77);
INSERT INTO authors_genres VALUES (5, 77);

INSERT INTO books VALUES (146, 'Păianjenul alb', 79, '9789734653249', 1959, 8.8, 'In 1938, celebrul alpinist Heinrich Harrer a reusit, impreuna cu citiva colegi, sa escaladeze fata nordica a Eigerului, in Alpii elvetieni. De-a lungul timpului, pe acest traseu, considerat printre cele mai dificile din lume, si-au pierdut viata peste saizeci de alpinisti.');
INSERT INTO books_genres VALUES (4, 146);
INSERT INTO books_genres VALUES (22, 146);
INSERT INTO books_genres VALUES (27, 146);

INSERT INTO books VALUES (148, 'Marea tăcere', 89, '9786069524695', 2021, 8.3, 'Marea tacere e opera lui completa, am primit un exemplar direct de la maestru, cu dedicatie. Haiku, tanka, renga toate magistral scrise si asezate intr-o arhitectura a unei structuri multinivelare. Un ADN poetic in perfecta constructie de sensuri multiple, codate in structuri temporale pe anotimpuri si zodii.');
INSERT INTO books_genres VALUES (2, 148);