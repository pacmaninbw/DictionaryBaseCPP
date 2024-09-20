#include <algorithm>
#include "ColumnDictionary.h"
#include <string>
#include <vector>

ColumnDictionary::ColumnDictionary()
{
    addDefinition(ColumnIds::DATE, "Date");
    addDefinition(ColumnIds::TEMPERATURE, "Temperature");
    addDefinition(ColumnIds::PUSLE_RATE, "Pulse Rate");
    addDefinition(ColumnIds::RESPIRATION_RATE, "Respiration Rate");
    addDefinition(ColumnIds::BLOOD_PRESSURE, "Blood Pressure");
    addDefinition(ColumnIds::BLOOD_OXYGEN, "Blood Oxygen");
    addDefinition(ColumnIds::WEIGHT, "Weight");
    addDefinition(ColumnIds::BLOOD_SUGAR, "Blood Glucose");
    addDefinition(ColumnIds::EXERCISE, "Exercise");
    addDefinition(ColumnIds::SLEEP_HOURS, "Sleep Hours");
    addDefinition(ColumnIds::SLEEP_INTERRUPTIONS, "Sleep Interruptions");
    addDefinition(ColumnIds::BOWEL_MOVEMENTS, "Bowel Movements");
    addDefinition(ColumnIds::NUTRITION_CALORIES, "Calories");
    addDefinition(ColumnIds::NUTRITION_SATURATED_FAT, "Saturated Fat");
    addDefinition(ColumnIds::NUTRITION_TRANS_FAT, "Trans Fat");
    addDefinition(ColumnIds::NUTRITION_CHOLESTEROL, "Cholesterol");
    addDefinition(ColumnIds::NUTRITION_SODIUM, "Sodium");
    addDefinition(ColumnIds::NUTRITION_FIBER, "Fiber");
    addDefinition(ColumnIds::NUTRITION_TOTAL_SUGARS, "Total Sugars");
    addDefinition(ColumnIds::NUTRITION_PROTIEN, "Protien");
    addDefinition(ColumnIds::NUTRITION_VITAMIN_D, "Vitamin D");
    addDefinition(ColumnIds::NUTRITION_CALCIUM, "Calcium");
    addDefinition(ColumnIds::NUTRITION_IRON, "Iron");
    addDefinition(ColumnIds::NUTRITION_POTASSIUM, "Potassium");
    addDefinition(ColumnIds::NOTES, "Notes");
}

