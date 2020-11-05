//void main()
//{
//	myRect(140, 10, 1140, 680, RGB(255, 255, 255), RGB(205, 231, 209));
//	myLine(140, 100, 1140, 100, RGB(0, 0, 0));
//	myLine(140, 590, 1140, 590, RGB(0, 0, 0));
//	myLine(260, 10, 260, 680, RGB(0, 0, 0));
//	myLine(1020, 10, 1020, 680, RGB(0, 0, 0));
//	int px = 344;
//	for (int x = 0; x < 8; x++)
//	{
//		myLine(px, 10, px, 100, RGB(0, 0, 0));
//		px += 84;
//	}
//	px = 344;
//	for (int x = 0; x < 8; x++)
//	{
//		myLine(px, 590, px, 680, RGB(0, 0, 0));
//		px += 84;
//	}
//	int py = 154;
//	for (int x = 0; x < 8; x++)
//	{
//		myLine(1020, py, 1140, py,RGB(0,0,0));
//		py += 54;
//	}
//	py = 154;
//	for (int x = 0; x < 8; x++)
//	{
//		myLine(140, py, 260, py, RGB(0, 0, 0));
//		py += 54;
//	}
//	myDrawTextWithFont(505, 310, 80, "Monopoly", RGB(255, 255, 255), RGB(229, 27, 27));
//	myRect(290, 155, 480, 270, RGB(255, 255, 255), RGB(92, 142, 224));
//	myDrawText(315, 205, 30, "COMMUNITY CHEST", RGB(255, 255, 255), RGB(92, 142, 224));
//	myRect(800, 420, 990, 535, RGB(255,255,255), RGB(214, 62, 62));
//	myDrawText(865, 470, 30, "CHANCE ?", RGB(255, 255, 255), RGB(214, 62, 62));
//	myDrawText(176, 40, 30, "START", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(266, 20, 30, "Iqbal Town\n       A", RGB(153, 51, 51), RGB(205, 231, 209));
//	myRect(262, 80, 343, 99, RGB(153, 51, 51), RGB(153, 51, 51));
//	myDrawText(350, 20, 30, "Community\n    Chest", RGB(92, 142, 224), RGB(205, 231, 209));
//	myDrawText(434, 20, 30, "Iqbal Town\n       B", RGB(153, 51, 51), RGB(205, 231, 209));
//	myRect(430, 80, 511, 99, RGB(153, 51, 51), RGB(153, 51, 51));
//	myDrawText(525, 20, 30, "Land Tax", RGB(0,0,0), RGB(205, 231, 209));
//	myDrawText(612, 20, 30, " Metro\nStation", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(696, 20, 30, "Kareem\n Block", RGB(153, 51, 51), RGB(205, 231, 209));
//	myRect(682, 80, 763, 99, RGB(153, 51, 51), RGB(153, 51, 51));
//	myDrawText(780, 20, 30, "Chance", RGB(214, 62, 62), RGB(205, 231, 209));
//	myDrawText(854, 20, 30, "Johar Town\n       A", RGB(0, 204, 204), RGB(205, 231, 209));
//	myRect(850, 80, 931, 99, RGB(0, 204, 204), RGB(0, 204, 204));
//	myDrawText(938, 20, 30, "Johar Town\n       B", RGB(0, 204, 204), RGB(205, 231, 209));
//	myRect(934, 80, 1019, 99, RGB(0, 204, 204), RGB(0, 204, 204));
//	myDrawText(1062, 40, 30, "JAIL", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(1046, 105, 30, "Faisal Town\n      A", RGB(255, 102, 153), RGB(205, 231, 209));
//	myRect(1022, 102, 1040, 153, RGB(255, 102, 153), RGB(255, 102, 153));
//	myDrawText(1050, 169, 30, "WASA", RGB(0,0,0), RGB(205, 231, 209));
//	myDrawText(1046, 213, 30, "Faisal Town\n      B", RGB(255, 102, 153), RGB(205, 231, 209));
//	myRect(1022, 210, 1040, 261, RGB(255, 102, 153), RGB(255, 102, 153));
//	myDrawText(1050, 277, 30, "PTCL", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(1046, 328, 30, "    Bus\n Station", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(1046, 375, 30, "Faisal Town\n      C", RGB(255, 102, 153), RGB(205, 231, 209));
//	myRect(1022, 372, 1040, 423, RGB(255, 102, 153), RGB(255, 102, 153));
//	myDrawText(1046, 429, 30, "Community\n    Chest", RGB(92, 142, 224), RGB(205, 231, 209));
//	myDrawText(1046, 483, 30, "Model Town\n      A", RGB(255, 209, 26), RGB(205, 231, 209));
//	myRect(1022, 480, 1040, 531, RGB(255, 209, 26), RGB(255, 209, 26));
//	myDrawText(1046, 537, 30, "Model Town\n      B", RGB(255, 209, 26), RGB(205, 231, 209));
//	myRect(1022, 534, 1040, 589, RGB(255, 209, 26), RGB(255, 209, 26));
//	myDrawText(1046, 626, 30, "PARKING", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(148, 626, 30, "GO TO PRISON", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(280, 627, 30, "DHA A", RGB(255, 255, 0), RGB(205, 231, 209));
//	myRect(262, 592, 343, 612, RGB(255, 255, 0), RGB(255, 255, 0));
//	myDrawText(365, 627, 30, "LESCO", RGB(0,0,0), RGB(205, 231, 209));
//	myDrawText(450, 627, 30, "Liberty", RGB(224, 102, 255), RGB(205, 231, 209));
//	myRect(430, 592, 511, 612, RGB(224, 102, 255), RGB(224, 102, 255));
//	myDrawText(522, 627, 30, "Gulberg B", RGB(224, 102, 255), RGB(205, 231, 209));
//	myRect(514, 592, 595, 612, RGB(224, 102, 255), RGB(224, 102, 255));
//	myDrawText(614, 617, 30, "Railway\n Station", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(712, 627, 30, "SUI", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(772, 627, 30, "Gulberg A", RGB(224, 102, 255), RGB(205, 231, 209));
//	myRect(766, 592, 847, 612, RGB(224, 102, 255), RGB(224, 102, 255));
//	myDrawText(864, 627, 30, "Chance", RGB(214, 62, 62), RGB(205, 231, 209));
//	myDrawText(942, 627, 30, "Link Road", RGB(255, 209, 26), RGB(205, 231, 209));
//	myRect(934, 592, 1019, 612, RGB(255, 209, 26), RGB(255, 209, 26));
//	myDrawText(143, 105, 30, "Bahria Town\n      C", RGB(0, 51, 204), RGB(205, 231, 209));
//	myRect(259, 102, 236, 153, RGB(0, 51, 204), RGB(0, 51, 204));
//	myDrawText(152, 169, 30, "Property Tax", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(143, 213, 30, "Bahria Town\n      B", RGB(0, 51, 204), RGB(205, 231, 209));
//	myRect(259, 210, 236, 261, RGB(0, 51, 204), RGB(0, 51, 204));
//	myDrawText(168, 277, 30, "Chance", RGB(214, 62, 62), RGB(205, 231, 209));
//	myDrawText(157, 328, 30, "Orange Train", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(143, 375, 30, "Bahria Town\n      A", RGB(0, 51, 204), RGB(205, 231, 209));
//	myRect(259, 372, 236, 423, RGB(0, 51, 204), RGB(0, 51, 204));
//	myDrawText(157, 429, 30, "Community\n    Chest", RGB(92, 142, 224), RGB(205, 231, 209));
//	myDrawText(160, 495, 30, "Y Block", RGB(255, 255, 0), RGB(205, 231, 209));
//	myRect(259, 480, 236, 531, RGB(255, 255, 0), RGB(255, 255, 0));
//	myDrawText(165, 547, 30, "DHA B", RGB(255, 255, 0), RGB(205, 231, 209));
//	myRect(259, 534, 236, 589, RGB(255, 255, 0), RGB(255, 255, 0));
//	system("pause");
//}

//void display_Board(int x = 140, int y = 10)
//{
//	myRect(x, y, x + 1000, y + 670, RGB(255, 255, 255), RGB(255, 255, 255));
//	myLine(x, y + 90, x + 1000, y + 90, RGB(0, 0, 0));
//	myLine(x, y + 580, x + 1000, y + 580, RGB(0, 0, 0));
//	myLine(x + 120, y, x + 120, y + 670, RGB(0, 0, 0));
//	myLine(x + 880, y, x + 880, y + 670, RGB(0, 0, 0));
//	int px = 204 + x;
//	for (int x = 0; x < 8; x++)
//	{
//		myLine(px, y, px, y + 90, RGB(0, 0, 0));
//		px += 84;
//	}
//	px = 204 + x;
//	for (int x = 0; x < 8; x++)
//	{
//		myLine(px, y + 580, px, y + 670, RGB(0, 0, 0));
//		px += 84;
//	}
//	int py = y + 144;
//	for (int i = 0; i < 8; i++)
//	{
//		myLine(x + 880, py, x + 1000, py, RGB(0, 0, 0));
//		py += 54;
//	}
//	py = y + 144;
//	for (int i = 0; i < 8; i++)
//	{
//		myLine(x, py, x + 120, py, RGB(0, 0, 0));
//		py += 54;
//	}
//	myDrawTextWithFont(x + 365, y + 300, 80, "Monopoly", RGB(255, 255, 255), RGB(229, 27, 27));
//	myRect(x + 150, y + 145, x + 340, y + 260, RGB(255, 255, 255), RGB(92, 142, 224));
//	myDrawText(x + 175, y + 195, 30, "COMMUNITY CHEST", RGB(255, 255, 255), RGB(92, 142, 224));
//	myRect(x + 660, y + 410, x + 850, y + 525, RGB(255, 255, 255), RGB(214, 62, 62));
//	myDrawText(x + 725, y + 460, 30, "CHANCE ?", RGB(255, 255, 255), RGB(214, 62, 62));
//	myDrawText(x + 36, y + 30, 30, "START", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 126, y + 10, 30, "Iqbal Town\n       A", RGB(153, 51, 51), RGB(205, 231, 209));
//	myRect(x + 122, y + 70, x + 203, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
//	myDrawText(x + 210, y + 10, 30, "Community\n    Chest", RGB(92, 142, 224), RGB(205, 231, 209));
//	myDrawText(x + 294, y + 10, 30, "Iqbal Town\n       B", RGB(153, 51, 51), RGB(205, 231, 209));
//	myRect(x + 290, y + 70, x + 371, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
//	myDrawText(x + 385, y + 10, 30, "Land Tax", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 472, y + 10, 30, " Metro\nStation", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 556, y + 10, 30, "Kareem\n Block", RGB(153, 51, 51), RGB(205, 231, 209));
//	myRect(x + 542, y + 70, x + 623, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
//	myDrawText(x + 640, y + 10, 30, "Chance", RGB(214, 62, 62), RGB(205, 231, 209));
//	myDrawText(x + 714, y + 10, 30, "Johar Town\n       A", RGB(0, 204, 204), RGB(205, 231, 209));
//	myRect(x + 710, y + 70, x + 791, y + 89, RGB(0, 204, 204), RGB(0, 204, 204));
//	myDrawText(x + 798, y + 10, 30, "Johar Town\n       B", RGB(0, 204, 204), RGB(205, 231, 209));
//	myRect(x + 794, y + 70, x + 879, y + 89, RGB(0, 204, 204), RGB(0, 204, 204));
//	myDrawText(x + 922, y + 30, 30, "JAIL", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 906, y + 95, 30, "Faisal Town\n      A", RGB(255, 102, 153), RGB(205, 231, 209));
//	myRect(x + 882, y + 92, x + 900, y + 143, RGB(255, 102, 153), RGB(255, 102, 153));
//	myDrawText(x + 910, y + 159, 30, "WASA", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 906, y + 203, 30, "Faisal Town\n      B", RGB(255, 102, 153), RGB(205, 231, 209));
//	myRect(x + 882, y + 200, x + 900, y + 251, RGB(255, 102, 153), RGB(255, 102, 153));
//	myDrawText(x + 910, y + 267, 30, "PTCL", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 906, y + 318, 30, "    Bus\n Station", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 906, y + 365, 30, "Faisal Town\n      C", RGB(255, 102, 153), RGB(205, 231, 209));
//	myRect(x + 882, y + 362, x + 900, y + 413, RGB(255, 102, 153), RGB(255, 102, 153));
//	myDrawText(x + 906, y + 419, 30, "Community\n    Chest", RGB(92, 142, 224), RGB(205, 231, 209));
//	myDrawText(x + 906, y + 473, 30, "Model Town\n      A", RGB(255, 209, 26), RGB(205, 231, 209));
//	myRect(x + 882, y + 470, x + 900, y + 521, RGB(255, 209, 26), RGB(255, 209, 26));
//	myDrawText(x + 906, y + 527, 30, "Model Town\n      B", RGB(255, 209, 26), RGB(205, 231, 209));
//	myRect(x + 882, y + 524, x + 900, y + 579, RGB(255, 209, 26), RGB(255, 209, 26));
//	myDrawText(x + 906, y + 616, 30, "PARKING", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 8, y + 616, 30, "GO TO PRISON", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 140, y + 617, 30, "DHA A", RGB(255, 255, 0), RGB(205, 231, 209));
//	myRect(x + 122, y + 582, x + 203, y + 602, RGB(255, 255, 0), RGB(255, 255, 0));
//	myDrawText(x + 225, y + 617, 30, "LESCO", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 310, y + 617, 30, "Liberty", RGB(224, 102, 255), RGB(205, 231, 209));
//	myRect(x + 290, y + 582, x + 371, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
//	myDrawText(x + 382, y + 617, 30, "Gulberg B", RGB(224, 102, 255), RGB(205, 231, 209));
//	myRect(x + 374, y + 582, x + 455, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
//	myDrawText(x + 474, y + 607, 30, "Railway\n Station", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 572, y + 617, 30, "SUI", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 632, y + 617, 30, "Gulberg A", RGB(224, 102, 255), RGB(205, 231, 209));
//	myRect(x + 626, y + 582, x + 707, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
//	myDrawText(x + 724, y + 617, 30, "Chance", RGB(214, 62, 62), RGB(205, 231, 209));
//	myDrawText(x + 802, y + 617, 30, "Link Road", RGB(255, 209, 26), RGB(205, 231, 209));
//	myRect(x + 794, y + 582, x + 879, y + 602, RGB(255, 209, 26), RGB(255, 209, 26));
//	myDrawText(x + 3, y + 95, 30, "Bahria Town\n      C", RGB(0, 51, 204), RGB(205, 231, 209));
//	myRect(x + 119, y + 92, x + 96, y + 143, RGB(0, 51, 204), RGB(0, 51, 204));
//	myDrawText(x + 12, y + 159, 30, "Property Tax", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 3, y + 203, 30, "Bahria Town\n      B", RGB(0, 51, 204), RGB(205, 231, 209));
//	myRect(x + 119, y + 200, x + 96, y + 251, RGB(0, 51, 204), RGB(0, 51, 204));
//	myDrawText(x + 28, y + 267, 30, "Chance", RGB(214, 62, 62), RGB(205, 231, 209));
//	myDrawText(x + 17, y + 318, 30, "Orange Train", RGB(0, 0, 0), RGB(205, 231, 209));
//	myDrawText(x + 3, y + 365, 30, "Bahria Town\n      A", RGB(0, 51, 204), RGB(205, 231, 209));
//	myRect(x + 119, y + 362, x + 96, y + 413, RGB(0, 51, 204), RGB(0, 51, 204));
//	myDrawText(x + 17, y + 419, 30, "Community\n    Chest", RGB(92, 142, 224), RGB(205, 231, 209));
//	myDrawText(x + 20, y + 485, 30, "Y Block", RGB(255, 255, 0), RGB(205, 231, 209));
//	myRect(x + 119, y + 470, x + 96, y + 521, RGB(255, 255, 0), RGB(255, 255, 0));
//	myDrawText(x + 25, y + 537, 30, "DHA B", RGB(255, 255, 0), RGB(205, 231, 209));
//	myRect(x + 119, y + 524, x + 96, y + 579, RGB(255, 255, 0), RGB(255, 255, 0));
//}