#include "rizTypes.h"
#include "timeconvert.h"
#include "keypointsUtil.h"
#include "qdebug.h"
#include "rizTypes.h"

namespace rizTypes {

	QColor ColorRGBA::toQColor()
	{
		return QColor(r,g,b,a);
	}

	int Line::findNote_time(float time)
	{
		return (bisectByKey<Note>(this->notes, time, [](Note x) {return x.time; }))-1;
	}
	int Line::findLinePoint_time(float time)
	{
		return (bisectByKey<LinePoint>(this->linePoints, time, [](LinePoint x) {return x.time; })) - 1;
	}


	float RizChart::getChartTime(float realTime)
	{
		int index = findKeypoint_floorPos(this->bpmShifts, realTime);
		return real2rizWrapped(this->bpmShifts[index], this->bpm, realTime);
	}

	float RizChart::fromChartTime(float rizTime)
	{
		int index = findKeypoint_time(this->bpmShifts, rizTime);
		return riz2realWrapped(this->bpmShifts[index], this->bpm, rizTime);
	}

	void RizChart::preprocessChart()
	{
        for (int i = 0; i < (int)this->canvasMoves.size(); i++)
		{
            for (int j = 0; j < (int)this->canvasMoves[i].speedKeyPoints.size(); j++)
			{
                this->canvasMoves[i].speedKeyPoints[j].time = this->fromChartTime(this->canvasMoves[i].speedKeyPoints[j].time);
			}
		}
	}
	
	void RizChart::updateChart(float time)
	{
		this->hitNotes.clear();
		for (int j = 0; j < this->lines.size(); j++)
		{
			for (int i = this->lines[j].findNote_time(time);  i < this->lines[j].notes.size() && this->lines[j].notes[i].time <= time; i++)
			{
				if (!this->lines[j].notes[i].isHit && this->lines[j].notes[i].time <= time)
				{
					this->hitNotes.push_back(i);
					this->lines[j].notes[i].isHit = true;
					int k = 1 + 1;
				}
				
			}
		}
	}

}
