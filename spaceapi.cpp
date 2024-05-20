#include "pch.h"
#include "spaceapi.h"

class HERO :public space::FACTORY
{
	public:

		HERO(float _x, float _y) :FACTORY(types::hero, _x, _y)
		{
			dir = dirs::right;
		}

		void Release() override
		{
			delete this;
		}
		int Move(float _speed) override
		{
			float what_speed = speed + _speed;

			switch (dir)
			{
			case dirs::up:
				if (y - what_speed >= 50.0f)
				{
					y -= what_speed;
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::down:
				if (ey + what_speed <= 650.0f)
				{
					y += what_speed;
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::right:
				if (ex + what_speed <= scr_width)
				{
					x += what_speed;
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::left:
				if (x - what_speed >= 0)
				{
					x -= what_speed;
					SetEdges();
					return DLL_OK;
				}

			case dirs::u_r:
				if (y - what_speed >= 50.0f && ex + what_speed <= scr_width)
				{
					LineData = InitLine(x, y, x + what_speed, y - 0.5f);
					x += what_speed;
					y = NextY(x);
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::u_l:
				if (y - what_speed >= 50.0f && x - what_speed >= 0)
				{
					LineData = InitLine(x, y, x - what_speed, y - 0.5f);
					x -= what_speed;
					y = NextY(x);
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::d_r:
				if (ey + what_speed <= 650.0f && ex + what_speed <= scr_width)
				{
					LineData = InitLine(x, y, x + what_speed, y + 0.5f);
					x += what_speed;
					y = NextY(x);
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::d_l:
				if (ey + what_speed <= 650.0f && x - what_speed >= 0)
				{
					LineData = InitLine(x, y, x - what_speed, y + 0.5f);
					x -= what_speed;
					y = NextY(x);
					SetEdges();
					return DLL_OK;
				}
				break;
			}

			return DLL_FAIL;
		}
		bool Shoot() override
		{
			shoot_delay--;
			if (shoot_delay <= 0)
			{
				shoot_delay = 50; 


				return true;
			}
			return false;
		}
};

class EVIL :public space::FACTORY
{
	public:

		EVIL(types what_type, float _x, float _y) :FACTORY(what_type, _x, _y)
		{
			if (_x < scr_width / 2)dir = dirs::right;
			else dir = dirs::left;
		}

		void Release()override
		{
			delete this;
		}
		int Move(float _speed) override
		{
			float what_speed = speed + _speed;

			switch (dir)
			{
			case dirs::up:
				if (y - what_speed >= 50.0f)
				{
					y -= what_speed;
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::down:
				if (ey + what_speed <= 650.0f)
				{
					y += what_speed;
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::right:
				if (ex + what_speed <= scr_width)
				{
					x += what_speed;
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::left:
				if (x - what_speed >= 0)
				{
					x -= what_speed;
					SetEdges();
					return DLL_OK;
				}

			case dirs::u_r:
				if (y - what_speed >= 50.0f && ex + what_speed <= scr_width)
				{
					LineData = InitLine(x, y, x + what_speed, y - 0.5f);
					x += what_speed;
					y = NextY(x);
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::u_l:
				if (y - what_speed >= 50.0f && x - what_speed >= 0)
				{
					LineData = InitLine(x, y, x - what_speed, y - 0.5f);
					x -= what_speed;
					y = NextY(x);
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::d_r:
				if (ey + what_speed <= 650.0f && ex + what_speed <= scr_width)
				{
					LineData = InitLine(x, y, x + what_speed, y + 0.5f);
					x += what_speed;
					y = NextY(x);
					SetEdges();
					return DLL_OK;
				}
				break;

			case dirs::d_l:
				if (ey + what_speed <= 650.0f && x - what_speed >= 0)
				{
					LineData = InitLine(x, y, x - what_speed, y + 0.5f);
					x -= what_speed;
					y = NextY(x);
					SetEdges();
					return DLL_OK;
				}
				break;
			}

			return DLL_FAIL;
		}
		bool Shoot() override
		{
			shoot_delay--;
			if (shoot_delay <= 0)
			{
				switch (type)
				{
				case types::evil1:
					shoot_delay = 80;
					break;

				case types::evil2:
					shoot_delay = 120;
					break;

				case types::evil3:
					shoot_delay = 100;
					break;
				}
				return true;
			}
			return false;
		}
};

//////////////////////////////////////////////////////

space::Person space::iCreatePerson(types who, float where_x, float where_y)
{
	space::Person ret = nullptr;

	switch (who)
	{
	case types::hero:
		ret = new HERO(where_x, where_y);
		break;

	case types::evil1:
		ret = new EVIL(types::evil1, where_x, where_y);
		break;

	case types::evil2:
		ret = new EVIL(types::evil2, where_x, where_y);
		break;

	case types::evil3:
		ret = new EVIL(types::evil3, where_x, where_y);
		break;
	}

	return ret;
}

space::LINEDATA space::InitLineData(float start_x, float start_y, float end_x, float end_y)
{
	LINEDATA ALine;

	if (abs(end_x - start_x) == 0)
	{
		ALine.intercept = 0;
		if (end_y > start_y) ALine.slope = 1.0f;
		else ALine.slope = -1.0f;
	}
	else
	{
		ALine.slope = (end_y - start_y) / (end_x - start_x);
		ALine.intercept = start_y - start_x * ALine.slope;
	}

	return ALine;
}
float space::NextLineY(float _next_x, space::LINEDATA& Data)
{
	return _next_x * Data.slope + Data.intercept;
}

space::AIOUTPUT space::AIToDo(space::AIDATA CurrentAction)
{
	space::LINEDATA Line;
	space::AIOUTPUT ToDo;

	space::InitLineData(CurrentAction.my_x, CurrentAction.my_y, CurrentAction.enemy_x, CurrentAction.enemy_y);

	if (!CurrentAction.enemy_in_range)
	{
		ToDo.new_action = choices::move;
		if ((CurrentAction.my_y >= CurrentAction.enemy_y && CurrentAction.my_y <= CurrentAction.enemy_ey)
			|| (CurrentAction.my_ey >= CurrentAction.enemy_y && CurrentAction.my_ey <= CurrentAction.enemy_ey))
		{
			if (CurrentAction.my_x > CurrentAction.enemy_x)ToDo.new_dir = dirs::left;
			else ToDo.new_dir = dirs::right;
		}
		else if (CurrentAction.my_y > CurrentAction.enemy_ey)
		{
			if ((CurrentAction.my_x >= CurrentAction.enemy_x && CurrentAction.my_x <= CurrentAction.enemy_ex)
				|| (CurrentAction.my_ex >= CurrentAction.enemy_x && CurrentAction.my_ex <= CurrentAction.enemy_ex))
				ToDo.new_dir = dirs::up;
			else if (CurrentAction.my_ex < CurrentAction.enemy_x)ToDo.new_dir = dirs::u_r;
			else ToDo.new_dir = dirs::u_l;
		}
		else if (CurrentAction.my_ey < CurrentAction.enemy_y)
		{
			if ((CurrentAction.my_x >= CurrentAction.enemy_x && CurrentAction.my_x <= CurrentAction.enemy_ex)
				|| (CurrentAction.my_ex >= CurrentAction.enemy_x && CurrentAction.my_ex <= CurrentAction.enemy_ex))
				ToDo.new_dir = dirs::down;
			else if (CurrentAction.my_ex < CurrentAction.enemy_x)ToDo.new_dir = dirs::d_r;
			else ToDo.new_dir = dirs::d_l;
		}
		ToDo.new_x = 0;
		ToDo.new_y = 0;
	}
	else
	{
		ToDo.new_action = choices::shoot;
		if ((CurrentAction.my_y >= CurrentAction.enemy_y && CurrentAction.my_y <= CurrentAction.enemy_ey)
			|| (CurrentAction.my_ey >= CurrentAction.enemy_y && CurrentAction.my_ey <= CurrentAction.enemy_ey))
		{
			if (CurrentAction.my_x > CurrentAction.enemy_x)ToDo.new_dir = dirs::left;
			else ToDo.new_dir = dirs::right;
		}
		else if (CurrentAction.my_y > CurrentAction.enemy_ey)
		{
			if ((CurrentAction.my_x = CurrentAction.enemy_x && CurrentAction.my_x <= CurrentAction.enemy_ex)
				|| (CurrentAction.my_ex >= CurrentAction.enemy_x && CurrentAction.my_ex <= CurrentAction.enemy_ex))
				ToDo.new_dir = dirs::up;
			else if (CurrentAction.my_ex < CurrentAction.enemy_x)ToDo.new_dir = dirs::u_r;
			else ToDo.new_dir = dirs::u_l;
		}
		else if (CurrentAction.my_ey < CurrentAction.enemy_y)
		{
			if ((CurrentAction.my_x >= CurrentAction.enemy_x && CurrentAction.my_x <= CurrentAction.enemy_ex)
				|| (CurrentAction.my_ex >= CurrentAction.enemy_x && CurrentAction.my_ex <= CurrentAction.enemy_ex))
				ToDo.new_dir = dirs::down;
			else if (CurrentAction.my_ex < CurrentAction.enemy_x)ToDo.new_dir = dirs::d_r;
			else ToDo.new_dir = dirs::d_l;
		}
		ToDo.new_x = ToDo.new_x = CurrentAction.my_x + CurrentAction.speed;
		ToDo.new_y = space::NextLineY(ToDo.new_x, Line);;
	}

	return ToDo;
}

