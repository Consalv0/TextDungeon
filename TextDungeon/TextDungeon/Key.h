#pragma once

ref class Door;

ref class Key : public DungeonObject {
public:
	Key(String ^name);
	Key();
	~Key();

	virtual property String^ Name {
		String^ get() override; void set(String^ x) override;
	}

	void Use() override;
};

