#ifndef RIZTYPE_H
#define RIZTYPE_H
#include "nlohmann/json.hpp"
#include <QColor>
class LinePointItem;
namespace rizTypes {
	//--------------------struct_bpmShifts--------------------
    struct KeyPoint{
		int easeType;
		float floorPosition;
		float value;
		float time;
        friend void to_json(nlohmann::json& j, const KeyPoint& p);
        friend void from_json(const nlohmann::json& j, KeyPoint& p);
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const KeyPoint& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["easeType"] = p.easeType;
		j["floorPosition"] = p.floorPosition;
		j["value"] = p.value;
		j["time"] = p.time;
	}

    void from_json(const nlohmann::json& j, KeyPoint& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("easeType").get_to(p.easeType);
		j.at("floorPosition").get_to(p.floorPosition);
		j.at("value").get_to(p.value);
		j.at("time").get_to(p.time);
		p.isHaveData = true;
	}
	//--------------------struct_cameraMove--------------------
    struct CameraMove{
        std::vector<KeyPoint> scaleKeyPoints;
        std::vector<KeyPoint> xPositionKeyPoints;
        friend void to_json(nlohmann::json& j, const CameraMove& p);
        friend void from_json(const nlohmann::json& j, CameraMove& p);
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const CameraMove& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["scaleKeyPoints"] = p.scaleKeyPoints;
		j["xPositionKeyPoints"] = p.xPositionKeyPoints;
	}

    void from_json(const nlohmann::json& j, CameraMove& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("scaleKeyPoints").get_to(p.scaleKeyPoints);
		j.at("xPositionKeyPoints").get_to(p.xPositionKeyPoints);
		p.isHaveData = true;
	}
	//--------------------struct_canvasMoves--------------------
	struct CanvasMove{
		int index;
        std::vector<KeyPoint> speedKeyPoints;
        std::vector<KeyPoint> xPositionKeyPoints;
		friend void to_json(nlohmann::json& j, const CanvasMove& p);
		friend void from_json(const nlohmann::json& j, CanvasMove& p);
	private:
		bool isHaveData;
	};
    struct Note{
        float floorPosition;
        std::vector<float> otherInformations;
        float time;
        int type;
        friend void to_json(nlohmann::json& j, const Note& p);
        friend void from_json(const nlohmann::json& j, Note& p);
		// Runtime Data
		bool isHit;
    private:
        bool isHaveData;
    };

	void to_json(nlohmann::json& j, const CanvasMove& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["index"] = p.index;
		j["speedKeyPoints"] = p.speedKeyPoints;
		j["xPositionKeyPoints"] = p.xPositionKeyPoints;
	}

	void from_json(const nlohmann::json& j, CanvasMove& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("index").get_to(p.index);
		j.at("speedKeyPoints").get_to(p.speedKeyPoints);
		j.at("xPositionKeyPoints").get_to(p.xPositionKeyPoints);
		p.isHaveData = true;
	}
	//--------------------struct_challengeTimes--------------------
    struct ChallengeTimes{
		float checkPoint;
		float start;
		float end;
		float transTime;
        friend void to_json(nlohmann::json& j, const ChallengeTimes& p);
        friend void from_json(const nlohmann::json& j, ChallengeTimes& p);
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const ChallengeTimes& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["checkPoint"] = p.checkPoint;
		j["start"] = p.start;
		j["end"] = p.end;
		j["transTime"] = p.transTime;
	}

    void from_json(const nlohmann::json& j, ChallengeTimes& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("checkPoint").get_to(p.checkPoint);
		j.at("start").get_to(p.start);
		j.at("end").get_to(p.end);
		j.at("transTime").get_to(p.transTime);
		p.isHaveData = true;
	}
	//--------------------struct_endColor--------------------
    struct ColorRGBA{
		int a;
		int b;
		int r;
		int g;
        friend void to_json(nlohmann::json& j, const ColorRGBA& p);
        friend void from_json(const nlohmann::json& j, ColorRGBA& p);
		QColor toQColor();
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const ColorRGBA& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["a"] = p.a;
		j["b"] = p.b;
		j["r"] = p.r;
		j["g"] = p.g;
	}

    void from_json(const nlohmann::json& j, ColorRGBA& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("a").get_to(p.a);
		j.at("b").get_to(p.b);
		j.at("r").get_to(p.r);
		j.at("g").get_to(p.g);
		p.isHaveData = true;
	}
	//--------------------struct_judgeRingColor--------------------
    struct JudgeRingColor{
        ColorRGBA endColor;
        ColorRGBA startColor;
		float time;
        friend void to_json(nlohmann::json& j, const JudgeRingColor& p);
        friend void from_json(const nlohmann::json& j, JudgeRingColor& p);
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const JudgeRingColor& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["endColor"] = p.endColor;
		j["startColor"] = p.startColor;
		j["time"] = p.time;
	}

    void from_json(const nlohmann::json& j, JudgeRingColor& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("endColor").get_to(p.endColor);
		j.at("startColor").get_to(p.startColor);
		j.at("time").get_to(p.time);
		p.isHaveData = true;
	}
	//--------------------struct_linePoints--------------------
    struct LinePoint{
		int canvasIndex;
		int easeType;
        ColorRGBA color;
		float floorPosition;
		float time;
		float xPosition;
        friend void to_json(nlohmann::json& j, const LinePoint& p);
        friend void from_json(const nlohmann::json& j, LinePoint& p);
		LinePointItem* parentItem;
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const LinePoint& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["canvasIndex"] = p.canvasIndex;
		j["easeType"] = p.easeType;
		j["color"] = p.color;
		j["floorPosition"] = p.floorPosition;
		j["time"] = p.time;
		j["xPosition"] = p.xPosition;
	}

    void from_json(const nlohmann::json& j, LinePoint& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("canvasIndex").get_to(p.canvasIndex);
		j.at("easeType").get_to(p.easeType);
		j.at("color").get_to(p.color);
		j.at("floorPosition").get_to(p.floorPosition);
		j.at("time").get_to(p.time);
		j.at("xPosition").get_to(p.xPosition);
		p.isHaveData = true;
	}
	//--------------------struct_lines--------------------
    struct Line{
        std::vector<JudgeRingColor> judgeRingColor;
        std::vector<ColorRGBA> lineColor;
        std::vector<LinePoint> linePoints;
        std::vector<Note> notes;
        friend void to_json(nlohmann::json& j, const Line& p);
        friend void from_json(const nlohmann::json& j, Line& p);
		int findNote_time(float time);
		int findLinePoint_time(float time);
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const Line& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["judgeRingColor"] = p.judgeRingColor;
		j["lineColor"] = p.lineColor;
		j["linePoints"] = p.linePoints;
		j["notes"] = p.notes;
	}

    void from_json(const nlohmann::json& j, Line& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("judgeRingColor").get_to(p.judgeRingColor);
		j.at("lineColor").get_to(p.lineColor);
		j.at("linePoints").get_to(p.linePoints);
		j.at("notes").get_to(p.notes);
		p.isHaveData = true;
	}
	//--------------------struct_notes--------------------


    void to_json(nlohmann::json& j, const Note& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["floorPosition"] = p.floorPosition;
		j["otherInformations"] = p.otherInformations;
		j["time"] = p.time;
		j["type"] = p.type;
	}

    void from_json(const nlohmann::json& j, Note& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("floorPosition").get_to(p.floorPosition);
		j.at("otherInformations").get_to(p.otherInformations);
		j.at("time").get_to(p.time);
		j.at("type").get_to(p.type);
		p.isHaveData = true;
		p.isHit = false;
	}
	//--------------------struct_themes--------------------
    struct ThemeData{
        std::vector<ColorRGBA> colorsList;
        friend void to_json(nlohmann::json& j, const ThemeData& p);
        friend void from_json(const nlohmann::json& j, ThemeData& p);
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const ThemeData& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["colorsList"] = p.colorsList;
	}

    void from_json(const nlohmann::json& j, ThemeData& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("colorsList").get_to(p.colorsList);
		p.isHaveData = true;
	}
	//--------------------struct_Bamboo_IN--------------------
    struct RizChart{
		std::string songsName;
		float bpm;
        std::vector<KeyPoint> bpmShifts;
        CameraMove cameraMove;
        std::vector<CanvasMove> canvasMoves;
        std::vector<Line> lines;
        std::vector<ChallengeTimes> challengeTimes;
		int fileVersion;
		float offset;
        std::vector<ThemeData> themes;
		// -------runTimeData--------
		std::vector<int> hitNotes;
        friend void to_json(nlohmann::json& j, const RizChart& p);
        friend void from_json(const nlohmann::json& j, RizChart& p);
        float getChartTime(float realTime);
		float fromChartTime(float rizTime);
		void preprocessChart();
		void updateChart(float time);
		
	private:
		bool isHaveData;
	};

    void to_json(nlohmann::json& j, const RizChart& p) {
		if (!p.isHaveData) {
			j = nlohmann::json::object();
			return;
		}
		j["songsName"] = p.songsName;
		j["bPM"] = p.bpm;
		j["bpmShifts"] = p.bpmShifts;
		j["cameraMove"] = p.cameraMove;
		j["canvasMoves"] = p.canvasMoves;
		j["lines"] = p.lines;
		j["challengeTimes"] = p.challengeTimes;
		j["fileVersion"] = p.fileVersion;
		j["offset"] = p.offset;
		j["themes"] = p.themes;
	}

    void from_json(const nlohmann::json& j, RizChart& p) {
		if (j.empty()) {
			p.isHaveData = false;
			return;
		}
		j.at("songsName").get_to(p.songsName);
		j.at("bPM").get_to(p.bpm);
		j.at("bpmShifts").get_to(p.bpmShifts);
		j.at("cameraMove").get_to(p.cameraMove);
		j.at("canvasMoves").get_to(p.canvasMoves);
		j.at("lines").get_to(p.lines);
		j.at("challengeTimes").get_to(p.challengeTimes);
		j.at("fileVersion").get_to(p.fileVersion);
		j.at("offset").get_to(p.offset);
		j.at("themes").get_to(p.themes);
		p.hitNotes = std::vector<int>();
		p.isHaveData = true;
	}
}
#endif