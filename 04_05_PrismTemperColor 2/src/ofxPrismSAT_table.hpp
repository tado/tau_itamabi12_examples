/**
***     ARTSAT Project
***
***     Copyright (C) 2011 - 2011 HORIGUCHI Junshi.
***     Version    openFrameworks
***     Homepage   http://iridium.jp/
***     E-mail     zap00365@nifty.com
***
***     This source code is for Xcode.
***     Xcode 4.0 (LLVM compiler 2.0)
***
***     ofxPrismSAT_table.hpp
**/

#ifndef __OFXPRISMSAT_TABLE_H
#define __OFXPRISMSAT_TABLE_H

struct TableRec {
    ofxPrismSAT::FormatEnum     format;
    ofxPrismSAT::UnitEnum       unit;
    char                        sql[32];
    char                        tag[64];
    union {
        struct {
            char                no[32];
            char                yes[32];
        } boolHint;
        struct {
            int                 lower;
            int                 upper;
        } intHint;
        struct {
            double              lower;
            double              upper;
        } doubleHint;
        struct {
            char                format[32];
        } ofxSATTimeHint;
    };
};

static  TableRec const*         GetTableBySensor    (ofxPrismSAT::SensorType sensor);
static  ofxPrismSAT::SensorType GetSensorByTag      (std::string const& tag);

static  TableRec const          ofxprismsat_table[] = {
    {
        .format                 = ofxPrismSAT::FORMAT_BOOL,
        .unit                   = ofxPrismSAT::UNIT_NONE,
        .sql                    = "mode",
        .tag                    = "モード",
        .boolHint               = {
            "ノーマル",
            "セーフ"
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_INT,
        .unit                   = ofxPrismSAT::UNIT_NONE,
        .sql                    = "time_shobc",
        .tag                    = "SH OBC時刻"
    },
    {
        .format                 = ofxPrismSAT::FORMAT_BOOL,
        .unit                   = ofxPrismSAT::UNIT_NONE,
        .sql                    = "control_attitude",
        .tag                    = "姿勢決定制御",
        .boolHint               = {
            "停止中",
            "動作中"
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_OFXSATTIME,
        .unit                   = ofxPrismSAT::UNIT_NONE,
        .sql                    = "time_rtc",
        .tag                    = "RTC時刻",
        .ofxSATTimeHint         = {
            "%YYYY/%MM/%DD %hh:%mm:%ss"
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_BOOL,
        .unit                   = ofxPrismSAT::UNIT_NONE,
        .sql                    = "control_camera",
        .tag                    = "カメラコントロール",
        .boolHint               = {
            "停止中",
            "動作中"
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_solar",
        .tag                    = "太陽電池電圧(V-SA)",
        .doubleHint             = {
             +7.7,
            +13.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_BOOL,
        .unit                   = ofxPrismSAT::UNIT_NONE,
        .sql                    = "schedule_camera",
        .tag                    = "撮影予約状態",
        .boolHint               = {
            "予約なし",
            "撮影待機(予約有)"
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_battery",
        .tag                    = "電池電圧(V-BATP)",
        .doubleHint             = {
            +8.0,
            +8.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_charge",
        .tag                    = "充電電流(I-BATC)",
        .doubleHint             = {
               +0.0,
            +1000.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_discharge",
        .tag                    = "放電電流(I-BATD)",
        .doubleHint             = {
              +0.0,
            +600.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarpxf",
        .tag                    = "太陽電池電流 (＋Xパネル表）",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarmxf",
        .tag                    = "太陽電池電流 (－Xパネル表）",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarpyf",
        .tag                    = "太陽電池電流 (＋Yパネル表）",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarmyf",
        .tag                    = "太陽電池電流 (－Yパネル表）",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarpxb",
        .tag                    = "太陽電池電流 (＋Xパネル裏）",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarmxb",
        .tag                    = "太陽電池電流 (－Xパネル裏）",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarpyb",
        .tag                    = "太陽電池電流 (＋Yパネル裏）",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarmyb",
        .tag                    = "太陽電池電流 (－Yパネル裏）",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarpxm",
        .tag                    = "太陽電池電流 (+X面本体)",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarmxm",
        .tag                    = "太陽電池電流 (-X面本体)",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarpym",
        .tag                    = "太陽電池電流 (+Y面本体)",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_solarmym",
        .tag                    = "太陽電池電流 (-Y面本体)",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_DEG_S,
        .sql                    = "gyro_x",
        .tag                    = "ジャイロ(X軸角速度)",
        .doubleHint             = {
            -2.0,
            +2.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_nT,
        .sql                    = "magnetometer_x",
        .tag                    = "磁気センサ(X)",
        .doubleHint             = {
            -99999.9,
            +99999.9
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_DEG_S,
        .sql                    = "gyro_y",
        .tag                    = "ジャイロ(Y軸角速度)",
        .doubleHint             = {
            -2.0,
            +2.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_nT,
        .sql                    = "magnetometer_y",
        .tag                    = "磁気センサ(Y)",
        .doubleHint             = {
            -99999.9,
            +99999.9
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_DEG_S,
        .sql                    = "gyro_z",
        .tag                    = "ジャイロ(Z軸角速度)",
        .doubleHint             = {
            -2.0,
            +2.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_nT,
        .sql                    = "magnetometer_z",
        .tag                    = "磁気センサ(Z)",
        .doubleHint             = {
            -99999.9,
            +99999.9
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_mainobc",
        .tag                    = "メインOBC温度",
        .doubleHint             = {
            +20.0,
            +50.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_maincamera",
        .tag                    = "メインカメラ温度",
        .doubleHint             = {
             +0.0,
            +20.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_outsidepx",
        .tag                    = "外壁温度(+X面)",
        .doubleHint             = {
            -40.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_outsidemx",
        .tag                    = "外壁温度(-X面)",
        .doubleHint             = {
            -40.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_outsidepy",
        .tag                    = "外壁温度(+Y面)",
        .doubleHint             = {
            -40.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_outsidemy",
        .tag                    = "外壁温度(-Y面)",
        .doubleHint             = {
            -40.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_outsidepz",
        .tag                    = "外壁温度(+Z面)",
        .doubleHint             = {
            -40.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_outsidemz",
        .tag                    = "外壁温度(-Z面)",
        .doubleHint             = {
            -40.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_panelpx",
        .tag                    = "パネル温度(+X)",
        .doubleHint             = {
            -70.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_panelmx",
        .tag                    = "パネル温度(-X)",
        .doubleHint             = {
            -70.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_panelpy",
        .tag                    = "パネル温度(+Y)",
        .doubleHint             = {
            -70.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_panelmy",
        .tag                    = "パネル温度(-Y)",
        .doubleHint             = {
            -70.0,
            +70.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_battery1",
        .tag                    = "電池温度1",
        .doubleHint             = {
             +0.0,
            +30.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_degC,
        .sql                    = "temperature_battery2",
        .tag                    = "電池温度2",
        .doubleHint             = {
             +0.0,
            +30.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_main33v",
        .tag                    = "メイン 3.3V系電流(I-E3.3)",
        .doubleHint             = {
              +0.0,
            +350.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_main50v",
        .tag                    = "メイン 5V系電流(I-E5)",
        .doubleHint             = {
             +0.0,
            +30.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_network",
        .tag                    = "通信系電流(I-TX)",
        .doubleHint             = {
              +0.0,
            +100.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_power",
        .tag                    = "電源系電流(I-P)",
        .doubleHint             = {
             +0.0,
            +50.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_mainreceiver",
        .tag                    = "メイン受信系電流(I-RXM)",
        .doubleHint             = {
             +0.0,
            +25.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_subreceiver",
        .tag                    = "サブ受信系電流(I-RXS)",
        .doubleHint             = {
             +0.0,
            +25.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_afsksender",
        .tag                    = "AFSK送信系電流(I-XL)",
        .doubleHint             = {
              +0.0,
            +200.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_gmsksender",
        .tag                    = "GMSK送信機電流(I-XH)",
        .doubleHint             = {
              +0.0,
            +200.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_mission50v",
        .tag                    = "ミッション系電流(I-O5)",
        .doubleHint             = {
             +0.0,
            +50.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_sensor",
        .tag                    = "センサー電流(I-SNS)",
        .doubleHint             = {
              +0.0,
            +100.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_heater",
        .tag                    = "ヒーター電流(I-HTR)",
        .doubleHint             = {
            +0.0,
            +0.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_mA,
        .sql                    = "current_expander",
        .tag                    = "展開系電流(I-DPL)",
        .doubleHint             = {
              +0.0,
            +500.0
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_main33v",
        .tag                    = "メイン 3.3V系電圧(VP-E3.3)",
        .doubleHint             = {
            +0.0,
            +3.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_main50v",
        .tag                    = "メイン 5V系電圧(V-E5)",
        .doubleHint             = {
            +0.0,
            +5.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_network",
        .tag                    = "通信系電圧(V-TX)",
        .doubleHint             = {
            +0.0,
            +5.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_power",
        .tag                    = "電源系電圧(V-P)",
        .doubleHint             = {
            +0.0,
            +5.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_mainreceiver",
        .tag                    = "メイン受信系電圧(V-RXM)",
        .doubleHint             = {
            +0.0,
            +5.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_subreceiver",
        .tag                    = "サブ受信系電圧(V-RXS)",
        .doubleHint             = {
            +0.0,
            +5.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_afsksender",
        .tag                    = "AFSK送信系電圧(V-XL)",
        .doubleHint             = {
            +0.0,
            +5.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_gmsksender",
        .tag                    = "GMSK送信機電圧(V-XH)",
        .doubleHint             = {
            +0.0,
            +5.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_mission50v",
        .tag                    = "ミッション5V系電圧(V-O5)",
        .doubleHint             = {
            +0.0,
            +5.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_mission33v",
        .tag                    = "ミッション3.3V系電圧(VP-03.3)",
        .doubleHint             = {
            +0.0,
            +3.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_heater",
        .tag                    = "ヒーター電圧(V-HTR)",
        .doubleHint             = {
             +0.0,
            +15.5
        }
    },
    {
        .format                 = ofxPrismSAT::FORMAT_DOUBLE,
        .unit                   = ofxPrismSAT::UNIT_V,
        .sql                    = "voltage_expander",
        .tag                    = "展開系電圧(V-DPL)",
        .doubleHint             = {
             +0.0,
            +15.5
        }
    }
};

static TableRec const* GetTableBySensor(ofxPrismSAT::SensorType sensor)
{
    TableRec const* result(NULL);
    
    if (0 <= sensor && sensor < lengthof(ofxprismsat_table)) {
        result = &ofxprismsat_table[sensor];
    }
    return result;
}

static ofxPrismSAT::SensorType GetSensorByTag(std::string const& tag)
{
    ofxPrismSAT::SensorType sensor;
    ofxPrismSAT::SensorType result(-1);
    
    for (sensor = 0; sensor < lengthof(ofxprismsat_table); ++sensor) {
        if (ofxprismsat_table[sensor].tag == tag) {
            result = sensor;
            break;
        }
    }
    return result;
}

#endif
