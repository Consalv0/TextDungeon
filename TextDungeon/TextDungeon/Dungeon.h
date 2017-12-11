#pragma once

ref class Dungeon abstract sealed {
public:
	static array<DungeonObject^> ^objects = gcnew array<DungeonObject^> {
	/* Keys */
		gcnew Key("&yKEY MADE OF STEEL&x"),                // 00
		gcnew Key("&yKEY MADE OF WOOD&x"),                 // 01
		gcnew Key("&yKEY MADE OF STONE&x"),                // 02
		gcnew Key("&yKEY MADE OF OBSIDEAN&x"),             // 03
		gcnew Key("&yKEY WITH DIAMONDS&x"),                // 04
		gcnew Key("&yKEY MADE OF AN EXTRANGE MATERIAL&x"), // 05
		gcnew Key("&yKEY MADE OF GOLD&x"),                 // 06
		gcnew Key("&yKEY COVERED WITH VINES&x"),           // 07
	};

	static array<Door^> ^doors = gcnew array<Door^> {
		gcnew Door("&rDOOR MADE OF STEEL&x",      objects[0]), // 00
		gcnew Door("&rDOOR COVERED OF ROOTS&x",   objects[1]), // 01
		gcnew Door("&rDOOR WITH DRESSED STONE&x", objects[2]), // 02
		gcnew Door("&rDOOR MADE OF LAVA&x",       objects[3]), // 03
		gcnew Door("&rDOOR MADE OF CRYSTALS&x",   objects[4]), // 04
		gcnew Door("&rDOOR WIDTHOUT SENSE&x",     objects[5]), // 05
		gcnew Door("&rDOOR MADE OF GOLD&x",       objects[6]), // 06
		gcnew Door("&rDOOR UNDER THE TREE&x",     objects[7]), // 07

	/* Normal Doors */
		gcnew Door("&gDOOR WITH A SKULL&x"),        // 08
		gcnew Door("&gDOOR WITH THE SPIDERWEB&x"),  // 09
		gcnew Door("&gDOOR MADE OF WOOD&x"),        // 10
		gcnew Door("&gDOOR COVERED WITH SLIME&x"),  // 11
		gcnew Door("&gDOOR MADE OF STONE&x"),       // 12
		gcnew Door("&gDOOR WITH A SKELETON&x"),     // 13
		gcnew Door("&gDOOR WITHOUT LATCH&x"),       // 14
		gcnew Door("&gDOOR UNDER THE CASCADE&x"),   // 15
		gcnew Door("&gDOOR WITH BARS&x"),           // 16
		gcnew Door("&gDOOR COVERED WITH PLANTS&x"), // 17
		gcnew Door("&gDOOR ON FIRE&x"),             // 18
		gcnew Door("&gDOOR MADE OF WOOD&x"),        // 19
	};

	static array<Room^> ^rooms = gcnew array<Room^> {
		gcnew Room(gcnew array<Door^>{doors[0 ], doors[8 ]           }, gcnew array<DungeonObject^>{objects[0 ]}, ""), // 00 <---- Probably the start
		gcnew Room(gcnew array<Door^>{doors[5 ]                      }, gcnew array<DungeonObject^>{           }, ""), // 01
		gcnew Room(gcnew array<Door^>{doors[8 ], doors[12]           }, gcnew array<DungeonObject^>{           }, ""), // 02
		gcnew Room(gcnew array<Door^>{doors[0 ], doors[9 ]           }, gcnew array<DungeonObject^>{objects[2 ]}, ""), // 03
		gcnew Room(gcnew array<Door^>{doors[10], doors[9 ], doors[1 ]}, gcnew array<DungeonObject^>{           }, ""), // 04
		gcnew Room(gcnew array<Door^>{doors[16], doors[12]           }, gcnew array<DungeonObject^>{           }, ""), // 05
		gcnew Room(gcnew array<Door^>{doors[1 ]                      }, gcnew array<DungeonObject^>{objects[7 ]}, ""), // 06
		gcnew Room(gcnew array<Door^>{doors[10], doors[11]           }, gcnew array<DungeonObject^>{           }, ""), // 07
		gcnew Room(gcnew array<Door^>{doors[16], doors[3 ], doors[17]}, gcnew array<DungeonObject^>{           }, ""), // 08
		gcnew Room(gcnew array<Door^>{doors[17], doors[11], doors[2 ]}, gcnew array<DungeonObject^>{           }, ""), // 09
		gcnew Room(gcnew array<Door^>{doors[18], doors[3 ]           }, gcnew array<DungeonObject^>{objects[4 ]}, ""), // 10
		gcnew Room(gcnew array<Door^>{doors[15], doors[2 ]           }, gcnew array<DungeonObject^>{           }, ""), // 11
		gcnew Room(gcnew array<Door^>{doors[4 ]                      }, gcnew array<DungeonObject^>{           }, ""), // 12
		gcnew Room(gcnew array<Door^>{doors[6 ], doors[18]           }, gcnew array<DungeonObject^>{           }, ""), // 13
		gcnew Room(gcnew array<Door^>{doors[14]                      }, gcnew array<DungeonObject^>{objects[ 5]}, ""), // 14
		gcnew Room(gcnew array<Door^>{doors[13], doors[15], doors[14]}, gcnew array<DungeonObject^>{           }, ""), // 15
		gcnew Room(gcnew array<Door^>{doors[7 ]                      }, gcnew array<DungeonObject^>{           }, ""), // 16
		gcnew Room(gcnew array<Door^>{doors[7 ], doors[6 ], doors[19]}, gcnew array<DungeonObject^>{           }, ""), // 17 <---- Probably the exit
		gcnew Room(gcnew array<Door^>{doors[5 ], doors[4 ], doors[13]}, gcnew array<DungeonObject^>{objects[ 3]}, ""), // 18
		gcnew Room(gcnew array<Door^>{doors[19]                      }, gcnew array<DungeonObject^>{objects[ 1]}, ""), // 19
	};

	static Door^ GetDoor(String ^name, Room ^room) {
		if (room == nullptr) return nullptr;
		int count = 0;
		Door ^door;
		for (int i = 0; i < room->doors->Length; i++) {
			array<String^> ^doorname = Writter::RemoveSyntax(Writter::RemoveColorSyntax(room->doors[i]->name))->Split(gcnew array<Char>{' '}, StringSplitOptions::RemoveEmptyEntries);
			if (Writter::Contains(name, doorname, 1)) {
				count++;
				door = room->doors[i];
			}
		}
		if (count == 0) {
			Console::Clear();
			Writter::WriteCenteredAt("There's no door or YOU are not specific enough with that kind of description, &rYOU feel bad.&x", int(Console::BufferWidth * .2), 0, int(Console::BufferWidth * .6F), Console::BufferHeight);
			Writter::ShowCursor(false);
			Console::ReadKey();
			Console::Clear();
			return nullptr;
		}
		if (count > 1) {
			Console::Clear();
			Writter::WriteCenteredAt("&rYOU can't open more than one door at the same time you are not any Good!&x", int(Console::BufferWidth * .2), 0,
				int(Console::BufferWidth * .6F), Console::BufferHeight);
			Writter::ShowCursor(false);
			Console::ReadKey();
			Console::Clear();
			return nullptr;
		}
		return door;
	}

};