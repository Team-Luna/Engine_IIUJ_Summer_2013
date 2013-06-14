#include "Level.h"
#include <exception>
#include <string>
#include <list>
#include <map>
#include <Windows.h>

		/*
			Wyœwietlanie debug output - jakbyœmy jeszcze potrzebowali jakiegos wyswietlenia
		
		#include <Windows.h>
		char msgbuf[10];

		OutputDebugString("============================\n");
		sprintf(msgbuf, "%f\n", lineOutput[7]);
		OutputDebugString(msgbuf);
		OutputDebugString("============================\n");
		*/

Level::Level(IrrlichtDevice* Device, char* path) {
	//Loads a level from a file
	device = Device;

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	pause = false;

	//Creating temporary variables
	std::string TempLine = "";
	char animT[15];
	const int modelP_size=50;
	char modelP[modelP_size];
	std::string LINE;
	double lineOutput[25];

	//Loading first batch of data
	ifstream infile;
	infile.open(path);
	
	//Starting point
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	start = Point(lineOutput[0], lineOutput[1], lineOutput[2]);
	
	//Level Size
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	size = Point(lineOutput[0], lineOutput[1], lineOutput[2]);
	
	//Respawn/starting point
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	respawn = Point(lineOutput[0], lineOutput[1], lineOutput[2]);
	
	//Custom attributes
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	custom_attribute1 = lineOutput[0];
	custom_attribute2 = lineOutput[1];
	custom_attribute3 = lineOutput[2];

	//Gravity
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	gravity = lineOutput[0];
	
	//Active range
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	active_range = Point(lineOutput[0], lineOutput[1], lineOutput[2]);
	
	//Time left of the level
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	time_left = lineOutput[0];
	
	//Initializing generic stuff
	lc_interval = 0;
	esc_interval = 0;
	delta_time = 0;
	std::list<Field*> Temp_f;
	fields = Temp_f;
	
	//Loading second batch of data
	//Initializing animation tables
	LINE = getNextRelevantLine(infile);
	std::map< std::string, AnimationTable* > Temp_at;
	animation_tables = Temp_at;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);

		//Creating the table
		std::string name = LINE;
		animation_tables.insert(std::pair< std::string, AnimationTable* >(name, new AnimationTable()));
		
		//Filling the table
		for (int j = 0; j < 12; j++)
		{
			LINE = getNextRelevantLine(infile);
			
			extractValues(LINE, lineOutput);
			int total = lineOutput[0];
			animation_tables.find(name)->second->push(j, total, -1);
			getline(infile, LINE);
			extractValues(LINE, lineOutput);
			for (int k = 0; k < total*2; k++)
				animation_tables.find(name)->second->push(j, k, lineOutput[k]);
		}
	}
	
	//Initializing player
	LINE = getNextRelevantLine(infile);
	TempLine = LINE;
	//Transforming std::strings to char arrays (animation table name)
	LINE = getNextRelevantLine(infile);
	for (int i = 0; i < 15; i++)
		animT[i] = 0;
	for (int i = 0; i < LINE.length(); i++)
		animT[i] = LINE[i];
	//Transforming std::strings to char arrays (model path)
	LINE = getNextRelevantLine(infile);
	for (int i = 0; i < modelP_size; i++)
		modelP[i] = 0;
	for(int i = 0; i < LINE.length(); i++)
		modelP[i] = LINE[i];
	//Creating player
	extractValues(TempLine, lineOutput);
	player = new Player(this, lineOutput[0], lineOutput[1], lineOutput[2], //movement speed, hit points, lives
		Point(lineOutput[3], lineOutput[4], lineOutput[5]), //starting point
		Point(lineOutput[6], lineOutput[7], lineOutput[8]), //size
		lineOutput[9], lineOutput[10], lineOutput[11], //custom values
		lineOutput[12], lineOutput[13], animT, modelP, //gravity degree, fancing angle
		Point(lineOutput[14], lineOutput[15], lineOutput[16]), lineOutput[17], lineOutput[18]); //translation, animated?, climbing?

	fields.insert(fields.end(), player->main_field);
	//Loading animator state
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	if (lineOutput[0]) //if set is needed, else go with default
		player->animator->set(lineOutput[1], lineOutput[2], //bool active, bool looping
			lineOutput[3], lineOutput[4], //animation id, animation speed
			lineOutput[5], lineOutput[6], lineOutput[7]); //current frame, min frame, max frame

	//Initializing items
	LINE = getNextRelevantLine(infile);
	std::list<Item*> Temp_i;
	items = Temp_i;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);
		TempLine = LINE;
		//Transforming std::strings to char arrays (animation table name)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 15; i++)
			animT[i] = 0;
		for (int i = 0; i < LINE.length(); i++)
			animT[i] = LINE[i];
		//Transforming std::strings to char arrays (model path)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < modelP_size; i++)
			modelP[i] = 0;
		for(int i = 0; i < LINE.length(); i++)
			modelP[i] = LINE[i];
		
		//Creating item
		extractValues(TempLine, lineOutput);
		Item* p = new Item(this, lineOutput[0], //movement speed
			Point(lineOutput[1], lineOutput[2], lineOutput[3]), //position
			Point(lineOutput[4], lineOutput[5], lineOutput[6]), //size
			lineOutput[7], lineOutput[8], lineOutput[9], lineOutput[10], //custom attributes, gravity degree
			lineOutput[11], animT, modelP, //facing angle, animation table, model path
			Point(lineOutput[12], lineOutput[13], lineOutput[14]), //translation
			lineOutput[15], lineOutput[16], lineOutput[17], lineOutput[18]); //animated?, life time, active, always active
		fields.insert(fields.end(), p->main_field);
		items.insert(items.end(), p);

		//Loading animator state
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		if (lineOutput[0]) //if set is needed, else go with default
			p->animator->set(lineOutput[1], lineOutput[2], //bool active, bool looping
				lineOutput[3], lineOutput[4], //animation id, animation speed
				lineOutput[5], lineOutput[6], lineOutput[7]); //current frame, min frame, max frame
	}
	
	//Initializing conditions
	LINE = getNextRelevantLine(infile);
	std::map< std::string, Condition* > Temp_cond;
	conditions = Temp_cond;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		Condition* c;
		Condition* c_a;
		Condition* c_b;
		Field* c_f;
		std::string temp;
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);

		int ID = (int)lineOutput[0];

		switch(ID)
		{
		case 1: //Complex
			//Getting first part
			LINE = getNextRelevantLine(infile);
			if (conditions.find(LINE) != conditions.end())
				c_a = conditions.find(LINE)->second;
			else c_a = 0;
			//Getting second part
			LINE = getNextRelevantLine(infile);
			if (conditions.find(LINE) != conditions.end())
				c_b = conditions.find(LINE)->second;
			else c_b = 0;
			//And / Or
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput); //1 = and, 0 = or
			//Creating condition and inserting it under a proper name
			c = new ConditionComplex(c_a, c_b, lineOutput[0]);
			LINE = getNextRelevantLine(infile);
			conditions.insert(std::pair< std::string, Condition* >(LINE, c));
			break;
		case 2: //Compare
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Creating condition and inserting it under a proper name
			c = new ConditionCompare(this, lineOutput[0], lineOutput[1], lineOutput[2], lineOutput[3], lineOutput[4]);
			LINE = getNextRelevantLine(infile);
			conditions.insert(std::pair< std::string, Condition* >(LINE, c));
			break;
		case 3: //Point
			//Getting values
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Getting next condition
			LINE = getNextRelevantLine(infile);
			if (conditions.find(LINE) != conditions.end())
				c_a = conditions.find(LINE)->second;
			else c_a = 0;
			//Creating condition and inserting it under a proper name
			c = new ConditionPoint(this, c_a, Point(lineOutput[0], lineOutput[1], lineOutput[2]), lineOutput[3], lineOutput[4]);
			LINE = getNextRelevantLine(infile);
			conditions.insert(std::pair< std::string, Condition* >(LINE, c));
			break;
		case 4: //Area
			//Getting field values
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			c_f = new Field(0, Point(lineOutput[0], lineOutput[1], lineOutput[2]), Point(lineOutput[3], lineOutput[4], lineOutput[5]),
				0, "", this, -1, Point(), false, true, true);
			fields.insert(fields.end(), c_f);
			//Creating condition and inserting it under a proper name
			c = new ConditionArea(c_f);
			LINE = getNextRelevantLine(infile);
			conditions.insert(std::pair< std::string, Condition* >(LINE, c));
		default:
			break;
		}
	}
	
	//Initializing events
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		Event* e;
		Event* e_next;
		Condition* c;
		std::string temp;

		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		int ID = lineOutput[0];
		
		if (ID == 1)
		{
			//Getting next event
			LINE = getNextRelevantLine(infile);
			if (event_dictionary.find(LINE) != event_dictionary.end())
				e_next = event_dictionary.find(LINE)->second;
			else e_next = 0;
			//Getting values
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Creating event and inserting it under a proper name
			e = new EventCP(this, lineOutput[0], lineOutput[1], lineOutput[2], lineOutput[3],
				lineOutput[4], lineOutput[5], lineOutput[6], lineOutput[7], e_next);
			LINE = getNextRelevantLine(infile);
			event_dictionary.insert(std::pair< std::string, Event* >(LINE, e));
		}
		if (ID == 2)
		{
			//Getting next event
			LINE = getNextRelevantLine(infile);
			if (event_dictionary.find(LINE) != event_dictionary.end())
				e_next = event_dictionary.find(LINE)->second;
			else e_next = 0;

			//Getting constructor values
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Getting monster name
			LINE = getNextRelevantLine(infile);
			//Creating the event
			EventSE* e_se = new EventSE(this, lineOutput[0], e_next, lineOutput[1],
				Point(lineOutput[2], lineOutput[3], lineOutput[4]),
				Point(lineOutput[5], lineOutput[6], lineOutput[7]),
				Point(lineOutput[8], lineOutput[9], lineOutput[10]),
				lineOutput[11], LINE);
			
			//Transforming std::strings to char arrays (animation table name)
			LINE = getNextRelevantLine(infile);
			for (int i = 0; i < 15; i++)
				animT[i] = 0;
			for (int i = 0; i < LINE.length(); i++)
				animT[i] = LINE[i];
			//Transforming std::strings to char arrays (model path)
			LINE = getNextRelevantLine(infile);
			for (int i = 0; i < modelP_size; i++)
				modelP[i] = 0;
			for(int i = 0; i < LINE.length(); i++)
				modelP[i] = LINE[i];
			//Loading second batch of data
			OutputDebugString(modelP);
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Setting new values
			e_se->set1(lineOutput[0], lineOutput[1], lineOutput[2],
				Point(lineOutput[3], lineOutput[4], lineOutput[5]), lineOutput[6],
				lineOutput[7], lineOutput[8], lineOutput[9], animT, modelP);
			
			//Loading second batch of data
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Getting monster_type
			LINE = getNextRelevantLine(infile);
			//Setting new values
			e_se->set2(lineOutput[0], lineOutput[1], lineOutput[2], lineOutput[3],
				lineOutput[4], lineOutput[5], lineOutput[6], lineOutput[7], lineOutput[8],
				lineOutput[9], LINE);
			//FINALLY putting created event into the dictionary
			LINE = getNextRelevantLine(infile);
			event_dictionary.insert(std::pair< std::string, Event* >(LINE, e_se));
		}
		if (ID == 3)
		{
			//Creating and inserting the event
			e = new EventDestroy(this);
			LINE = getNextRelevantLine(infile);
			event_dictionary.insert(std::pair< std::string, Event* >(LINE, e));
		}
		if (ID == 4)
		{
			//Getting next event
			LINE = getNextRelevantLine(infile);
			if (event_dictionary.find(LINE) != event_dictionary.end())
				e_next = event_dictionary.find(LINE)->second;
			else e_next = 0;
			
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Creating and inserting the event
			e = new EventDamage(this, lineOutput[0], e_next);
			LINE = getNextRelevantLine(infile);
			event_dictionary.insert(std::pair< std::string, Event* >(LINE, e));
		}
		if (ID == 5)
		{
			//Getting next event
			LINE = getNextRelevantLine(infile);
			if (event_dictionary.find(LINE) != event_dictionary.end())
				e_next = event_dictionary.find(LINE)->second;
			else e_next = 0;
			
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Creating and inserting the event
			e = new EventLevel(this, lineOutput[0], Point(lineOutput[1], lineOutput[2], lineOutput[3]), e_next);
			LINE = getNextRelevantLine(infile);
			event_dictionary.insert(std::pair< std::string, Event* >(LINE, e));
		}
	}
	
	//Initializing triggers
	LINE = getNextRelevantLine(infile);
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		Condition* c;
		Event* e;

		//Getting condition
		LINE = getNextRelevantLine(infile);
		if (conditions.find(LINE) != conditions.end())
			c = conditions.find(LINE)->second;
		else c = 0;
		//Getting event
		LINE = getNextRelevantLine(infile);
		if (event_dictionary.find(LINE) != event_dictionary.end())
			e = event_dictionary.find(LINE)->second;
		else e = 0;
		//Getting trigger input data
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		//Creating event and inserting it under a proper name
		Trigger* t = new Trigger(c, e, lineOutput[0]);
		LINE = getNextRelevantLine(infile);
		triggers.insert(std::pair< std::string, Trigger* >(LINE, t));
	}

	//Initializing actions
	LINE = getNextRelevantLine(infile);
	std::map< std::string, Action* > Temp_act;
	actions = Temp_act;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		Action* a;
		Action* a_next;
		Action* a_extra;
		Condition* c;
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);

		int ID = (int)lineOutput[0];

		switch(ID)
		{
		case 1: //Unit
			//Getting next Action
			LINE = getNextRelevantLine(infile);
			if (actions.find(LINE) != actions.end())
				a_next = actions.find(LINE)->second;
			else a_next = 0;
			//Getting Action ID
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Creating actual action
			a = new ActionUnit(this, lineOutput[0], a_next);
			//Inserting action into map
			LINE = getNextRelevantLine(infile);
			actions.insert(std::pair< std::string, Action* >(LINE, a));
			break;
		case 2: //Evaluate
			//Getting next Action
			LINE = getNextRelevantLine(infile);
			if (actions.find(LINE) != actions.end())
				a_next = actions.find(LINE)->second;
			else a_next = 0;
			//Getting Evaluate
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Creating actual action
			a = new ActionEvaluate(this, lineOutput[0], a_next);
			//Inserting action into map
			LINE = getNextRelevantLine(infile);
			actions.insert(std::pair< std::string, Action* >(LINE, a));
			break;
		case 3: //Wait
			//Getting condition
			LINE = getNextRelevantLine(infile);
			if (conditions.find(LINE) != conditions.end())
				c = conditions.find(LINE)->second;
			else c = 0;
			//Getting next Action
			LINE = getNextRelevantLine(infile);
			if (actions.find(LINE) != actions.end())
				a_next = actions.find(LINE)->second;
			else a_next = 0;
			//Getting Values
			LINE = getNextRelevantLine(infile);
			extractValues(LINE, lineOutput);
			//Creating actual action
			a = new ActionWait(this, lineOutput[0], lineOutput[1], c, a_next);
			//Inserting action into map
			LINE = getNextRelevantLine(infile);
			actions.insert(std::pair< std::string, Action* >(LINE, a));
			break;
		case 4: //If/Then/Else
			//Getting condition
			LINE = getNextRelevantLine(infile);
			if (conditions.find(LINE) != conditions.end())
				c = conditions.find(LINE)->second;
			else c = 0;
			//Getting next Action
			LINE = getNextRelevantLine(infile);
			if (actions.find(LINE) != actions.end())
				a_next = actions.find(LINE)->second;
			else a_next = 0;
			//Getting extra Action
			LINE = getNextRelevantLine(infile);
			if (actions.find(LINE) != actions.end())
				a_extra = actions.find(LINE)->second;
			else a_extra = 0;
			//Creating actual action
			a = new ActionIfThenElse(this, c, a_next, a_extra);
			//Inserting action into map
			LINE = getNextRelevantLine(infile);
			actions.insert(std::pair< std::string, Action* >(LINE, a));
			break;
		case 5: //Loop
			//Getting next Action
			LINE = getNextRelevantLine(infile);
			if (actions.find(LINE) != actions.end())
				a_next = actions.find(LINE)->second;
			else a_next = 0;
			//Getting extra Action
			LINE = getNextRelevantLine(infile);
			if (actions.find(LINE) != actions.end())
				a_extra = actions.find(LINE)->second;
			else a_extra = 0;
			//Creating actual action
			a = new ActionLoop(this, a_next, a_extra);
			//Inserting action into map
			LINE = getNextRelevantLine(infile);
			actions.insert(std::pair< std::string, Action* >(LINE, a));
			break;
		default:
			break;
		}
	}

	//Initializing action tables
	LINE = getNextRelevantLine(infile);
	std::map< std::string, AITable* > Temp_aitable;
	action_tables = Temp_aitable;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);
		std::string name = LINE;
		action_tables.insert(std::pair< std::string, AITable* >(name, new AITable()));

		//Obstackle
		LINE = getNextRelevantLine(infile);
		if (actions.find(LINE) != actions.end())
			action_tables.find(name)->second->actions[0] = actions.find(LINE)->second;
		//Cliff
		LINE = getNextRelevantLine(infile);
		if (actions.find(LINE) != actions.end())
			action_tables.find(name)->second->actions[1] = actions.find(LINE)->second;
		//Monster
		LINE = getNextRelevantLine(infile);
		if (actions.find(LINE) != actions.end())
			action_tables.find(name)->second->actions[2] = actions.find(LINE)->second;
		//Player
		LINE = getNextRelevantLine(infile);
		if (actions.find(LINE) != actions.end())
			action_tables.find(name)->second->actions[3] = actions.find(LINE)->second;
		//Side
		LINE = getNextRelevantLine(infile);
		if (actions.find(LINE) != actions.end())
			action_tables.find(name)->second->actions[4] = actions.find(LINE)->second;
	}

	//Initializing monsters
	LINE = getNextRelevantLine(infile);
	std::list<Monster*> Temp_m;
	monsters = Temp_m;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		std::string lineName;
		std::string lineMonsterType;
		LINE = getNextRelevantLine(infile);
		TempLine = LINE;
		//Transforming std::strings to char arrays (animation table name)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 15; i++)
			animT[i] = 0;
		for (int i = 0; i < LINE.length(); i++)
			animT[i] = LINE[i];
		//Transforming std::strings to char arrays (model path)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < modelP_size; i++)
			modelP[i] = 0;
		for(int i = 0; i < LINE.length(); i++)
			modelP[i] = LINE[i];
		//Getting monster name and type
		lineName = getNextRelevantLine(infile);
		lineMonsterType = getNextRelevantLine(infile);

		extractValues(TempLine, lineOutput);
		Monster* m = new Monster(this, lineOutput[0], lineOutput[1], //movement speed, hit points
			lineName, lineMonsterType, //name, monster type,
			Point(lineOutput[2], lineOutput[3], lineOutput[4]), //position
			Point(lineOutput[5], lineOutput[6], lineOutput[7]), //size
			lineOutput[8], lineOutput[9], lineOutput[10], lineOutput[11], //custom attributes, gravity degree
			lineOutput[12], animT, modelP, //facing angle, animation table, model path
			Point(lineOutput[13], lineOutput[14], lineOutput[15]), //translation
			lineOutput[16], lineOutput[17], lineOutput[18], lineOutput[19], lineOutput[20]); //animated?, life time, active, always active, climbing?
		fields.insert(fields.end(), m->main_field);
		monsters.insert(monsters.end(), m);
		
		//Loading animator state
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		if (lineOutput[0]) //if set is needed, else go with default
			m->animator->set(lineOutput[1], lineOutput[2], //bool active, bool looping
				lineOutput[3], lineOutput[4], //animation id, animation speed
				lineOutput[5], lineOutput[6], lineOutput[7]); //current frame, min frame, max frame
		
		//Loading AI
		LINE = getNextRelevantLine(infile);
		AITable* AIi1 = action_tables.find(LINE)->second;
		
		LINE = getNextRelevantLine(infile);
		Action* AIi2;
		if (actions.find(LINE) != actions.end())
			AIi2 = actions.find(LINE)->second;
		else AIi2 = 0;
		
		LINE = getNextRelevantLine(infile);
		Action* AIi3;
		if (actions.find(LINE) != actions.end())
			AIi3 = actions.find(LINE)->second;
		else AIi3 = 0;

		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		m->aI = new MonsterAI(m, AIi1, AIi2, AIi3, lineOutput[0], lineOutput[1], lineOutput[2]);
	}
	
	//Initializing Borders
	LINE = getNextRelevantLine(infile);
	std::list<Border*> Temp_b;
	boundaries = Temp_b;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);
		TempLine = LINE;
		//Transforming std::strings to char arrays (animation table name)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < 15; i++)
			animT[i] = 0;
		for (int i = 0; i < LINE.length(); i++)
			animT[i] = LINE[i];
		//Transforming std::strings to char arrays (model path)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < modelP_size; i++)
			modelP[i] = 0;
		for(int i = 0; i < LINE.length(); i++)
			modelP[i] = LINE[i];
		
		//Creating border
		extractValues(TempLine, lineOutput);
		Border* b = new Border(this, lineOutput[0], lineOutput[1], lineOutput[2], //movement speed, absolute, bouncing
			Point(lineOutput[3], lineOutput[4], lineOutput[5]), //position
			Point(lineOutput[6], lineOutput[7], lineOutput[8]), //size
			lineOutput[9], lineOutput[10], lineOutput[11], lineOutput[12], //custom attributes, gravity degree
			lineOutput[13], lineOutput[14], animT, modelP, //facing angle, model type, animation table, model path
			Point(lineOutput[15], lineOutput[16], lineOutput[17]), //translation
			lineOutput[18], lineOutput[19], lineOutput[20], lineOutput[21]); //animated?, life time, active, always active
		fields.insert(fields.end(), b->main_field);
		boundaries.insert(boundaries.end(), b);

		//Loading animator state
		LINE = getNextRelevantLine(infile);
		extractValues(LINE, lineOutput);
		if (lineOutput[0]) //if set is needed, else go with default
			b->animator->set(lineOutput[1], lineOutput[2], //bool active, bool looping
				lineOutput[3], lineOutput[4], //animation id, animation speed
				lineOutput[5], lineOutput[6], lineOutput[7]); //current frame, min frame, max frame
	}

	//Initializing BgMovableObject
	LINE = getNextRelevantLine(infile);
	std::list<BgMovableObject*> Temp_bgo;
	bgobjects = Temp_bgo;
	extractValues(LINE, lineOutput);
	for (int i = lineOutput[0]; 0 < i; i--)
	{
		LINE = getNextRelevantLine(infile);
		TempLine = LINE;
		//Transforming std::strings to char arrays (model path)
		LINE = getNextRelevantLine(infile);
		for (int i = 0; i < modelP_size; i++)
			modelP[i] = 0;
		for(int i = 0; i < LINE.length(); i++)
			modelP[i] = LINE[i];

		//Creating bgobject
		extractValues(TempLine, lineOutput);
		BgMovableObject* p = new BgMovableObject(this, Point(lineOutput[0], lineOutput[1], lineOutput[2]), //position
			Point(lineOutput[3], lineOutput[4], lineOutput[5]), //scale
			modelP, lineOutput[6], //texture, type
			Point(lineOutput[7], lineOutput[8], lineOutput[9])); //movement

		bgobjects.insert(bgobjects.end(), p);
	}

	bg_sky = new Background(vector3df(500,350,0), vector3df(1,1,1000), false, "../media/environment/sky16.JPG", 0.1, 1.0, device, player);
	bg_trees = new Background(vector3df(20,10,0), vector3df(-300,1,300), true, "../media/environment/trees.png", 0.5, 3.1, device, player);
	bg_beach = new Background(vector3df(800,200,0), vector3df(1,-1000,600), false, "../media/environment/beach.jpg", 5.1, 10.1, device, player);


	
	// Initializing Sound
	LINE = getNextRelevantLine(infile);

	for(int i=0; i<modelP_size; i++)
		modelP[i] = 0;
	for(int i=0; i<LINE.length(); i++)
		modelP[i] = LINE[i];

	se = createIrrKlangDevice();
	se->play2D(modelP, true);


	infile.close();
}

void Level::add_event(std::string init) {
	throw "Not yet implemented";
}

void Level::add_border(EventSE* Creator) {
	//Creating border
	Border* b = new Border(this, Creator->ms, Creator->abs, Creator->b, //movement speed, absolute, bouncing
		Creator->pos, //position
		Creator->size, //size
		Creator->ca1, Creator->ca2, Creator->ca3, Creator->gd, //custom attributes, gravity degree
		Creator->fa, Creator->mt, Creator->animT, Creator->modelP, //facing angle, model type, animation table, model path
		Creator->trans, //translation
		Creator->anim, Creator->lt, Creator->a, Creator->aa); //animated?, life time, active, always active
	fields.insert(fields.end(), b->main_field);
	boundaries.insert(boundaries.end(), b);
	
	//Loading animator state
	if (Creator->load) //if set is needed, else go with default
		b->animator->set(Creator->ac, Creator->lo, //bool active, bool looping
			Creator->aid, Creator->as, //animation id, animation speed
			Creator->curf, Creator->minf, Creator->maxf); //current frame, min frame, max frame
}

void Level::add_monster(EventSE* Creator) {
	//Creating monster
	Monster* m = new Monster(this, Creator->ms, Creator->hit_points, //movement speed, hit points
		"spawned_monster", Creator->monster_type, //name, monster type,
		Creator->pos, //position
		Creator->size, //size
		Creator->ca1, Creator->ca2, Creator->ca3, Creator->gd, //custom attributes, gravity degree
		Creator->fa, Creator->animT, Creator->modelP, //facing angle, animation table, model path
		Creator->trans, //translation
		Creator->anim, Creator->lt, Creator->a, Creator->aa, 0); //animated?, life time, active, always active, climbing?
	fields.insert(fields.end(), m->main_field);
	monsters.insert(monsters.end(), m);

	//Loading animator state
	if (Creator->load) //if set is needed, else go with default
		m->animator->set(Creator->ac, Creator->lo, //bool active, bool looping
			Creator->aid, Creator->as, //animation id, animation speed
			Creator->curf, Creator->minf, Creator->maxf); //current frame, min frame, max frame
}

void Level::add_item(EventSE* Creator) {
	//Creating item
	Item* p = new Item(this, Creator->ms, //movement speed
		Creator->pos, //position
		Creator->size, //size
		Creator->ca1, Creator->ca2, Creator->ca3, Creator->gd, //custom attributes, gravity degree
		Creator->fa, Creator->animT, Creator->modelP, //facing angle, animation table, model path
		Creator->trans, //translation
		Creator->anim, Creator->lt, Creator->a, Creator->aa); //animated?, life time, active, always active
	fields.insert(fields.end(), p->main_field);
	items.insert(items.end(), p);
	//Loading animator state
	if (Creator->load) //if set is needed, else go with default
		p->animator->set(Creator->ac, Creator->lo, //bool active, bool looping
			Creator->aid, Creator->as, //animation id, animation speed
			Creator->curf, Creator->minf, Creator->maxf); //current frame, min frame, max frame
}

void Level::add_bgobject(Point start){

}

void Level::turn_around(Field* field)
{
	if (field->owner->facing_angle == 90)
		field->owner->facing_angle = 270;
	else field->owner->facing_angle = 90;
}

void Level::move_forward(Field* field)
{
	if (field->owner->animator != 0)
		if (field->owner->animator->getAnimation() != 1)
			field->owner->animator->setAnimation(1);
	double o = 0;
	if (field->owner->facing_angle == 90)
		o = 1;
	else o = -1;
	if (field->velocity.position_x != o*field->owner->movement_speed)
		field->velocity.position_x = o*field->owner->movement_speed;
}

void Level::jump_forward(Field* field)
{
	//Animation
	if (field->owner->animator != 0)
		if (field->owner->animator->getAnimation() != 7)
			field->owner->animator->setAnimation(7);

	double o = 0;
	if (field->owner->facing_angle == 90)
		o = 1;
	else o = -1;
	
	//Y speed
	field->velocity.position_y = 2*field->owner->movement_speed;
	//X speed
	field->velocity.position_x = o*field->owner->movement_speed;
}

void Level::jump_backwards(Field* field)
{
	double o = 0;
	if (field->owner->facing_angle == 90)
		o = 1;
	else o = -1;
	
	//Y speed
	field->velocity.position_y = 2*field->owner->movement_speed;
	//X speed
	field->velocity.position_x = -o*field->owner->movement_speed;

	//Animation
	if (field->owner->animator != 0)
		field->owner->animator->setAnimation(7);
}

void Level::climb_upwards(Field* field)
{
	//Animation
	if (field->owner->animator != 0)
		if (field->owner->animator->getAnimation() != 10)
			field->owner->animator->setAnimation(10);

	//Y speed
	field->velocity.position_y = field->owner->movement_speed;
	//X speed
	field->velocity.position_x = 0;

	double o = 0;
	if (field->owner->facing_angle == 90)
		o = 1;
	else o = -1;

	//Checking Field
	Field* F = collision_Point(field->position + Point(o*8, 0, 0));
	if (F == 0)
		return;
	if (F->owner == 0)
		return;
	if (F->owner->get_type() != 4)
		return;
	if (F->owner->custom_attribute1 != 1)
		return;
	
	//Starting to climb
	if (field->owner->custom_attribute1 == 0)
	{
		field->owner->custom_attribute1 = 1;
		if (o == 1)
			field->position.position_x = F->position.position_x - (2 + F->size.position_x + field->size.position_x)/2;
		else
			field->position.position_x = F->position.position_x + (2 + F->size.position_x + field->size.position_x)/2;
	}
}

void Level::climb_downwards(Field* field)
{
	//Animation
	if (field->owner->animator != 0)
		if (field->owner->animator->getAnimation() != 10)
		{
			field->owner->animator->setAnimation(10);
			field->owner->animator->setSpeed(-15);
		}

	//Y speed
	field->velocity.position_y = -field->owner->movement_speed;
	//X speed
	field->velocity.position_x = 0;

	double o = 0;
	if (field->owner->facing_angle == 90)
		o = 1;
	else o = -1;

	//Checking Field
	Field* F = collision_Point(field->position + Point(o*3, -9, 0));
	if (F == 0)
		return;
	if (F->owner == 0)
		return;
	if (F->owner->get_type() != 4)
		return;
	if (F->owner->custom_attribute1 != 1)
		return;
	
	//Starting to climb
	if (field->owner->custom_attribute1 == 0)
	{
		field->owner->custom_attribute1 = 1;
		if (o == 1)
		{
			field->position.position_x = F->position.position_x + (2 + F->size.position_x + field->size.position_x)/2;
			field->position.position_y = F->position.position_y + (F->size.position_y)/2;
		}
		else
		{
			field->position.position_x = F->position.position_x - (2 + F->size.position_x + field->size.position_x)/2;
			field->position.position_y = F->position.position_y + (F->size.position_y)/2;
		}
		if (field->owner->facing_angle == 90)
			field->owner->facing_angle = 270;
		else field->owner->facing_angle = 90;
	}
}

void Level::attack(Field* field)
{
	//Animation
	if (field->owner->animator != 0)
		if (field->owner->animator->getAnimation() != 3)
			field->owner->animator->setAnimation(3);

	//X speed
	field->velocity.position_x = 0;
	
	double o = 0;
	if (field->owner->facing_angle == 90)
		o = 1;
	else o = -1;

	Field* f = collision_Point(field->position + Point(o*(5+field->size.position_x/2), 0, 0));
	damage(f, 20);
}

void Level::shoot(Field* field)
{
	//Animation
	if (field->owner->animator != 0)
		field->owner->animator->setAnimation(5);
}

void Level::idle(Field* field)
{
	//X speed
	field->velocity.position_x = 0;
	//Animation
	if (field->owner->animator != 0)
		field->owner->animator->setAnimation(0);
}

void Level::stop(Field* field, bool grounded)
{
	//Y speed
	field->velocity.position_y = 0;
	//X speed
	field->velocity.position_x = 0;

	if (grounded)
		field->owner->animator->setAnimation(0);
	else field->owner->animator->stop();
}

void Level::stop_climbing(Field* field)
{
	//Animation
	field->owner->animator->setSpeed(15);
	//Y speed
	field->velocity.position_y = 0;
	//X speed
	field->velocity.position_x = 0;

	double o = 0;
	if (field->owner->facing_angle == 90)
		o = 1;
	else o = -1;
	Field* F = collision_Point(field->position + Point(o*7, 6, 0));
	if (F == 0)
	{
		F = collision_Point(field->position + Point(o*5, 0, 0));
		field->position = F->position;
		field->position.position_y += (2 + F->size.position_y + field->size.position_y)/2;
	}
	
	if (field->owner != 0)
		field->owner->custom_attribute1 = 0;
}

void Level::advance_frame(ICameraSceneNode *cam) {
	//Handling pause status
	if (esc_interval > 0)
		esc_interval--;
	if (pause)
	{
		for (std::list<Field*>::iterator i = fields.begin(); i != fields.end(); i++)
			if ((*i)->owner != 0)
				if ((*i)->owner->animator != 0)
					(*i)->owner->animator->stop();
		return;
	}

	//Checking player position (if inside level)
	double x1 = start.position_x;
	double y1 = start.position_y;
	double z1 = start.layer;
	double x2 = x1 + size.position_x;
	double y2 = y1 + size.position_y;
	double z2 = z1 + size.layer;

	/*
	//Debug write up
	char msgbuf[40];
	sprintf(msgbuf, "Level: x1=%f", x1);
	OutputDebugString(msgbuf);
	sprintf(msgbuf, " x2=%f", x2);
	OutputDebugString(msgbuf);
	sprintf(msgbuf, " y1=%f", y1);
	OutputDebugString(msgbuf);
	sprintf(msgbuf, " y2=%f", y2);
	OutputDebugString(msgbuf);
	sprintf(msgbuf, " z1=%f", z1);
	OutputDebugString(msgbuf);
	sprintf(msgbuf, " z2=%f\n", z2);
	OutputDebugString(msgbuf);
	sprintf(msgbuf, "Player: x=%f", player->main_field->position.position_x);
	OutputDebugString(msgbuf);
	sprintf(msgbuf, " y=%f", player->main_field->position.position_y);
	OutputDebugString(msgbuf);
	sprintf(msgbuf, " z=%f\n", player->main_field->position.layer);
	OutputDebugString(msgbuf);
	*/

	if ((player->main_field->position.position_x < x1) || (x2 < player->main_field->position.position_x))
		player_death();
	if ((player->main_field->position.position_y < y1) || (y2 < player->main_field->position.position_y))
		player_death();
	if ((player->main_field->position.layer < z1) || (z2 < player->main_field->position.layer))
		player_death();

	//Handling triggers
	for (std::map< std::string, Trigger* >::iterator i = triggers.begin(); i != triggers.end(); i++)
	{
		if (i->second->takes_units)
			for (std::list<Field*>::iterator j = fields.begin(); j != fields.end(); j++)
				i->second->check((*j), 0);
		else i->second->check();
	}

	//Updating positions/scales/rotations:
	for (std::list<Field*>::iterator i = fields.begin(); i != fields.end(); i++)
		(*i)->update();
	//clearing garbage
	for (std::list<Field*>::iterator i = garbage.begin(); i != garbage.end(); i++)
		if ((*i)->owner != 0)
			(*i)->owner->remove();
		else {
			fields.remove(*i);
			delete(*i);
		}
	garbage.clear();
	
	//BgMovableObjects move
	for (std::list<BgMovableObject*>::iterator i = bgobjects.begin(); i != bgobjects.end(); i++)
		(*i)->move();

	//centralizing camera on player (if exists)
	if (player != 0 && cam != 0) {
		//position
		cam->setPosition(core::vector3df(player->main_field->position.position_x,
			player->main_field->position.position_y+15,(player->main_field->position.layer-1)*10-40));
		//target
		cam->setTarget(core::vector3df(player->main_field->position.position_x,
			player->main_field->position.position_y,(player->main_field->position.layer-1)*10));
	}

	//handling player velocity changes and animation
	if (player->main_field->velocity.position_x == 0)
	{
		if (player->animator->getAnimation() != 0)
			player->animator->setAnimation(0);
	}
	else
	{
		if (player->animator->getAnimation() != 1)
			player->animator->setAnimation(1);
	}

	//Handling player grounding
	player->main_field->position.position_y -= 1.0;
	if (collision_detect(player->main_field))
		player->grounded = true;
	else player->grounded = false;
	player->main_field->position.position_y += 1.0;
	if (player->grounded)
		player->main_field->velocity.position_x = 0;
	//player->main_field->velocity.position_y = 0; //player->main_field->get_vy()

	//AI
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		(*i)->act(delta_time);

	//decrementing layer change delay
	if (lc_interval > 0)
		lc_interval--;
}

bool Level::collision_detect(Field* source) {
	if (source->owner == 0) //Empty field, used for triggers
		return false;
	if (source->owner->custom_attribute3 == 1) //this field lacks collision
		return false;
	std::list<Field*>::iterator target = fields.begin();
	bool p = false;
	while (target != fields.end())
	{
		//Checking for redundant comparisons (different z levels, source-source)
		if (source->position.layer < ((*target)->position.layer - (*target)->size.layer / 2))
		{
			++target;
			continue;
		}
		if (((*target)->position.layer + (*target)->size.layer / 2) < source->position.layer)
		{
			++target;
			continue;
		}
		if ((*target) == source)
		{
			++target;
			continue;
		}
		//Checking if the field is empty
		if ((*target)->owner == 0)
		{
			++target;
			continue;
		}
		//Checking if the field has collision
		if ((*target)->owner->custom_attribute3 == 1)
		{
			++target;
			continue;
		}
			
		//Vefining values for further usage
		bool collided = false;

		double tx1 = (*target)->position.position_x - (*target)->size.position_x / 2;
		double tx2 = (*target)->position.position_x + (*target)->size.position_x / 2;
		double ty1 = (*target)->position.position_y - (*target)->size.position_y / 2;
		double ty2 = (*target)->position.position_y + (*target)->size.position_y / 2;

		double sx1 = source->position.position_x - source->size.position_x / 2;
		double sx2 = source->position.position_x + source->size.position_x / 2;
		double sy1 = source->position.position_y - source->size.position_y / 2;
		double sy2 = source->position.position_y + source->size.position_y / 2;

		//Collision is detected corner wise, checking if any of the 4 corners is inside of other object
		//Checking target inside source (vertical collision)
		if (sx1 <= tx1 && tx1 <= sx2)
		{
			if (sy1 <= ty1 && ty1 <= sy2)
				collided = true;
			if (sy1 <= ty2 && ty2 <= sy2)
				collided = true;
		}
		if (sx1 <= tx2 && tx2 <= sx2)
		{
			if (sy1 <= ty1 && ty1 <= sy2)
				collided = true;
			if (sy1 <= ty2 && ty2 <= sy2)
				collided = true;
		}
		//Checking source inside target (horizontal collision)
		if (tx1 < sx1 && sx1 < tx2)
		{
			if (ty1 < sy1 && sy1 < ty2)
				collided = true;
			if (ty1 < sy2 && sy2 < ty2)
				collided = true;
		}
		if (tx1 < sx2 && sx2 < tx2)
		{
			if (ty1 < sy1 && sy1 < ty2)
				collided = true;
			if (ty1 < sy2 && sy2 < ty2)
				collided = true;
		}
		
		//Handling collision (if any)
		if (collided)
		{
			if (source->owner!=NULL && ((source->owner)->get_type())&((*target)->type))
			{
						if((*target)->collision_effect!=NULL)
							(*target)->collision_effect->invokeEvent(*target,source);
			}
			if ((*target)->owner!=NULL && (((*target)->owner)->get_type())&(source->type))
			{
						if (source->collision_effect!=NULL)
							source->collision_effect->invokeEvent(source,*target);
			}
			p = true;
		}
		++target;
	}
	return p;
}

bool Level::inside(Field* field, Field* area)
{
	double fx = field->position.position_x;
	double fy = field->position.position_y;
	double fz = field->position.layer;

	double ax1 = area->position.position_x - area->size.position_x / 2;
	double ax2 = area->position.position_x + area->size.position_x / 2;
	double ay1 = area->position.position_y - area->size.position_y / 2;
	double ay2 = area->position.position_y + area->size.position_y / 2;
	double az1 = area->position.layer - area->size.layer / 2;
	double az2 = area->position.layer + area->size.layer / 2;

	if (ax1 <= fx && fx <= ax2)
		if (ay1 <= fy && fy <= ay2)
			if (az1 <= fz && fz <= az2)
				return true;
	return false;
}

Field* Level::collision_Point(Point p)
{
	std::list<Field*>::iterator target = fields.begin();
	while (target != fields.end())
	{
		if ((*target)->owner == 0) //Empty field, used for triggers
		{
			++target;
			continue;
		}
		if ((*target)->owner->custom_attribute3 == 1) //this field lacks collision
		{
			++target;
			continue;
		}

		//Checking collision
		double x1 = (*target)->position.position_x - (*target)->size.position_x / 2;
		double x2 = (*target)->position.position_x + (*target)->size.position_x / 2;
		double y1 = (*target)->position.position_y - (*target)->size.position_y / 2;
		double y2 = (*target)->position.position_y + (*target)->size.position_y / 2;
		double l1 = (*target)->position.layer - (*target)->size.layer / 2;
		double l2 = (*target)->position.layer + (*target)->size.layer / 2;

		if ((l1 < p.layer) && (p.layer < l2))
			if ((x1 < p.position_x) && (p.position_x < x2))
				if ((y1 < p.position_y) && (p.position_y < y2))
					return (*target);

		++target;
	}
	return 0;
}

void Level::move_field(Field* field) {
	Point base = field->position;
	switch (field->movement_type) {
	default:
		if (field->owner != 0)
			field->position.position_x += field->velocity.position_x * field->owner->movement_speed * delta_time;
		if (collision_detect(field))
		{
			field->position.position_x = base.position_x;
			field->velocity.position_x = 0;
		}
		if (field->owner != 0)
			field->position.position_y += field->velocity.position_y * field->owner->movement_speed * delta_time;
		if (collision_detect(field))
		{
			field->position.position_y = base.position_y;
			field->velocity.position_y = 0;
		}
		break;
	}
	//--field->time_left;
}

void Level::demove_field(Field* field) {
	Point t = field->position;
	switch (field->movement_type) {
	case -1: {
		break;
			 }
	case 'u':{
		t= t-field->velocity*field->owner->movement_speed*delta_time;	
		break;
			}
	}
	field->position = t;
	field->time_left = 0;
}

void Level::remove_player(Field* field) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		delete(player);
		player = 0;
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_border(Field* field, Border* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		boundaries.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_monster(Field* field, Monster* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		monsters.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_item(Field* field, Item* entity) {
	if (field == 0)
		return;
	//Removing entity:
	if (player != 0) {
		items.remove(entity);
		delete(entity);
	}
	//Removing field:
	fields.remove(field);
	delete(field);
}

void Level::remove_bgobject(BgMovableObject* entity) {
	//Removing entity:
	if (player != 0) {
		bgobjects.remove(entity);
		delete(entity);
	}
}

void Level::trash(Field* field) {
	//field->destroy_event.invoke() ??
	garbage.insert(garbage.end(), field);
}

void Level::process_key(irr::EKEY_CODE keycode) {
	if (player == 0)
		return;
	
	if (keycode == irr::KEY_ESCAPE)
	{
		if (esc_interval != 0)
			return;
		esc_interval = 30;
		pause = !pause;
		if (!pause)
			for (std::list<Field*>::iterator i = fields.begin(); i != fields.end(); i++)
				if ((*i)->owner != 0)
					if ((*i)->owner->animator != 0)
						(*i)->owner->animator->resume();
	}
	if (!control_enabled)
		return;

	if (keycode == irr::KEY_KEY_W)
		if (player->grounded)
			jump_forward(player->main_field);
	/*
	if (keycode == irr::KEY_KEY_S)
		if (player->grounded)
			player->main_field->velocity.position_y = -player->movement_speed*2;
	*/
	if (keycode == irr::KEY_KEY_D)
	{
		player->facing_angle = 90;
		player->main_field->velocity.position_x = player->movement_speed;
	}
	if (keycode == irr::KEY_KEY_A)
	{
		player->facing_angle = 270;
		player->main_field->velocity.position_x = -player->movement_speed;
	}
	if (keycode == irr::KEY_KEY_Q)
	{
		if (!player->grounded)
			return;
		if (lc_interval != 0)
			return;
		lc_interval = 30;
		player->main_field->position.layer += 1;
		bg_sky->moveInwards();
		bg_trees->moveOutwards();
		bg_beach->moveOutwards();
		if (collision_detect(player->main_field))
			player->main_field->position.layer -= 1;
	}
	if (keycode == irr::KEY_KEY_Z)
	{
		if (!player->grounded)
			return;
		if (lc_interval != 0)
			return;
		lc_interval = 30;
		player->main_field->position.layer -= 1;
		bg_sky->moveOutwards();
		bg_trees->moveInwards();
		bg_beach->moveInwards();
		if (collision_detect(player->main_field))
			player->main_field->position.layer += 1;
	}
}


double Level::retrieveValue(int type, Field* From, Field* To)
{
	if (From == 0)
		return 0;
	if (type == 1)
		return From->position.position_x;
	if (type == 2)
		return From->position.position_y;
	if (type == 3)
		return From->position.layer;
	if (type == 4)
		return From->velocity.position_x;
	if (type == 5)
		return From->velocity.position_y;
	if (type == 6)
		return From->velocity.layer;
	if (type == 7)
		return From->owner->custom_attribute1;
	if (type == 8)
		return From->owner->custom_attribute2;
	if (type == 9)
		return From->owner->custom_attribute3;
	if (type == 10)
		return From->owner->facing_angle;
	if (type == 11)
	{
		if (To == 0)
			return 0;
		double Ans = abs(From->position.position_x - To->position.position_x);
		Ans += abs(From->position.position_y - To->position.position_y);
		Ans = sqrt(Ans);
		return Ans;
	}
	if (type == 12)
		if (From->owner != 0)
			return From->owner->get_type();
	if (type == 13)
		if (From->owner != 0)
			if (From->owner->animator != 0)
				return From->owner->animator->checkProgress();
	if (type == 14)
		return delta_time;
	return 0;
}

void Level::editValue(int type, Field* From, double New)
{
	if (type == 1)
		From->position.position_x = New;
	if (type == 2)
		From->position.position_y = New;
	if (type == 3)
		From->position.layer = New;
	if (type == 4)
		From->velocity.position_x = New;
	if (type == 5)
		From->velocity.position_y = New;
	if (type == 6)
		From->velocity.layer = New;
	if (type == 7)
		From->owner->custom_attribute1 = New;
	if (type == 8)
		From->owner->custom_attribute2 = New;
	if (type == 9)
		From->owner->custom_attribute3 = New;
	if (type == 10)
		From->owner->facing_angle = New;
}

void Level::damage(Field* f, double amount)
{
	if (f == 0)
		return;
	if (f->owner == 0)
		return;
	if (f->owner->get_type() > 2)
		return;
	//Finding the monster who owns this field
	Monster* M = 0;
	for (std::list<Monster*>::iterator i = monsters.begin(); i != monsters.end(); i++)
		if ((*i)->main_field == f)
			M = (*i);
	//Dealing damage
	if (M != 0)
	{
		M->hp -= amount;
	
		//Handling death
		if (M->hp <= 0)
		{
			M->animator->setAnimation(11);
			M->aI->dead = true;
			M->custom_attribute3 = 1; //ignore collision
		}
	}
	else
	{
		player->hp -= amount;
		if (player->hp <= 0)
			player_death();
	}
}

void Level::player_respawn()
{
	control_enabled = true;
}

void Level::player_death()
{
	control_enabled = false;
	OutputDebugString("Player died.\n");
}

void Level::victory()
{

}
void Level::defeat()
{

}

inline std::string Level::getNextRelevantLine(ifstream& infile) {
	std::string ans = "";
	getline(infile, ans);
	//Skipping non-relevant lines
	while (ans.empty() || ans[0] == '#') //empty spacing line or comment
		getline(infile, ans);
	return ans;
}

void Level::extractValues(std::string source, double* output) {
	int n = 0;
	int i = 0;
	bool negative = false;
	double ans = 0.0;
	int decimal = 0;
	while (i < source.length())
	{
		if (source[i] == '-')
			negative = true;
		else
			if (source[i] == '.')
				decimal = 10;
			else
				if (source[i] != ' ')
				{
					if (decimal == 0)
						ans = ans*10 + source[i] - 48; //non-decimal
					else
					{
						//decimal
						ans += (double)(source[i] - 48)/(double)decimal;
						decimal *= 10;
					}
				}
				else
				{
					//Negative/positive and reset
					if (!negative)
						output[n++] = ans;
					else output[n++] = -ans;
					negative = false;
					ans = 0.0;
					decimal=0;
				}
		i++;
	}
	//Adding last value
	if (!negative)
		output[n++] = ans;
	else output[n++] = -ans;
}