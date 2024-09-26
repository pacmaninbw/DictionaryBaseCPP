#include <algorithm>
#include "ColumnDictionary.h"
#include <string>
#include <vector>

ColumnDictionary::ColumnDictionary()
: GenericDictionary(ColumnIds::NO_COLUMN, ColumnIds::LAST_COLUMN_ID,
    {
        {ColumnIds::DATE, "Date"},
        {ColumnIds::TEMPERATURE, "Temperature"},
        {ColumnIds::PUSLE_RATE, "Pulse Rate"},
        {ColumnIds::RESPIRATION_RATE, "Respiration Rate"},
        {ColumnIds::BLOOD_PRESSURE, "Blood Pressure"},
        {ColumnIds::BLOOD_OXYGEN, "Blood Oxygen"},
        {ColumnIds::WEIGHT, "Weight"},
        {ColumnIds::BLOOD_SUGAR, "Blood Glucose"},
        {ColumnIds::EXERCISE, "Exercise"},
        {ColumnIds::SLEEP_HOURS, "Sleep Hours"},
        {ColumnIds::SLEEP_INTERRUPTIONS, "Sleep Interruptions"},
        {ColumnIds::BOWEL_MOVEMENTS, "Bowel Movements"},
        {ColumnIds::NUTRITION_CALORIES, "Calories"},
        {ColumnIds::NUTRITION_SATURATED_FAT, "Saturated Fat"},
        {ColumnIds::NUTRITION_TRANS_FAT, "Trans Fat"},
        {ColumnIds::NUTRITION_CHOLESTEROL, "Cholesterol"},
        {ColumnIds::NUTRITION_SODIUM, "Sodium"},
        {ColumnIds::NUTRITION_FIBER, "Fiber"},
        {ColumnIds::NUTRITION_TOTAL_SUGARS, "Total Sugars"},
        {ColumnIds::NUTRITION_PROTIEN, "Protien"},
        {ColumnIds::NUTRITION_VITAMIN_D, "Vitamin D"},
        {ColumnIds::NUTRITION_CALCIUM, "Calcium"},
        {ColumnIds::NUTRITION_IRON, "Iron"},
        {ColumnIds::NUTRITION_POTASSIUM, "Potassium"},
        {ColumnIds::NOTES, "Notes"}
    })
{
}

