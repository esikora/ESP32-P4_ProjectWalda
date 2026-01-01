import json
import re
from collections import Counter, defaultdict
from copy import deepcopy

FOLDER = "main/"

HEADER_FILE = FOLDER + "quiz_data.h"
OUTPUT_FILE = FOLDER + "quiz_data_balanced.h"

# ------------------------------------------------------------
# Hilfsfunktion: C-String extrahieren
# ------------------------------------------------------------
def extract_string(value: str) -> str:
    s = value.strip()
    if s.startswith('"') and s.endswith('"'):
        s = s[1:-1]
    return s

# ------------------------------------------------------------
# Kommagetrennte Felder trennen, aber Strings respektieren
# ------------------------------------------------------------
def split_fields_respecting_strings(block: str):
    fields = []
    current = []
    in_string = False
    escape = False

    for ch in block:
        if in_string:
            current.append(ch)
            if escape:
                escape = False
            else:
                if ch == "\\":
                    escape = True
                elif ch == '"':
                    in_string = False
        else:
            if ch == '"':
                in_string = True
                current.append(ch)
            elif ch == ",":
                field = "".join(current).strip()
                if field:
                    fields.append(field)
                current = []
            else:
                current.append(ch)

    last = "".join(current).strip()
    if last:
        fields.append(last)

    return fields

# ------------------------------------------------------------
# quiz_data.h einlesen und Fragen extrahieren
# ------------------------------------------------------------
def parse_quiz_data(filename):
    with open(filename, "r", encoding="utf-8") as f:
        content = f.read()

    array_match = re.search(
        r"quiz_question_t\s+quiz_questions\s*\[\]\s*=\s*\{(.*?)\};",
        content,
        re.DOTALL,
    )
    if not array_match:
        raise ValueError("Konnte das Array 'quiz_question_t quiz_questions[]' nicht finden.")

    array_content = array_match.group(1)
    blocks = re.findall(r"\{([^{}]*)\}", array_content, re.DOTALL)

    questions = []
    for block in blocks:
        block_clean = re.sub(r"//.*", "", block).strip()
        fields = split_fields_respecting_strings(block_clean)

        if len(fields) < 9:
            continue

        q = {
            "question":          extract_string(fields[0]),
            "answer_a":          extract_string(fields[1]),
            "answer_b":          extract_string(fields[2]),
            "answer_c":          extract_string(fields[3]),
            "correct":           fields[4].strip().strip("'"),
            "difficulty":        fields[5].strip().strip("'"),
            "category":          fields[6].strip(),
            "correct_reaction":  extract_string(fields[7]),
            "wrong_reaction":    extract_string(fields[8]),
        }
        questions.append(q)

    return questions, content

# ------------------------------------------------------------
# Verteilung je Kategorie berechnen
# ------------------------------------------------------------
def count_correct_per_category(questions):
    per_cat = defaultdict(Counter)
    for q in questions:
        per_cat[q["category"]][q["correct"]] += 1
    return per_cat

# ------------------------------------------------------------
# Antwort-Anzahl prüfen, ob Gleichverteilung verletzt ist
# ------------------------------------------------------------
def is_category_balanced(counts, target):
    # Werte extrahieren
    a, b, c = counts["A"], counts["B"], counts["C"]

    # 1. Kein Wert darf mehr als target + 1 sein
    if max(a, b, c) > target + 1:
        return False

    # 2. Es dürfen höchstens zwei Werte target + 1 sein
    if min(a, b, c) < target:
        return False

    # Wenn wir hier sind, ist die Kategorie akzeptabel verteilt
    return True

# ------------------------------------------------------------
# Antworten permutieren, um Gleichverteilung je Kategorie zu erreichen
# ------------------------------------------------------------
def balance_per_category(questions):
    balanced = deepcopy(questions)

    # Kategorien gruppieren
    categories = defaultdict(list)
    for q in balanced:
        categories[q["category"]].append(q)

    # Jede Kategorie einzeln balancieren
    for cat, qlist in categories.items():
        total = len(qlist)
        target = total // 3

        counts = Counter(q["correct"] for q in qlist)

        print(f"\nKategorie {cat}:")
        print("  vorher:", counts, ", gesamt: ", total)
        print("  Ziel je Buchstabe:", target)

        if is_category_balanced(counts, target):
            print("  bereits ausbalanciert")
            continue

        groups = {
            "A": [q for q in qlist if q["correct"] == "A"],
            "B": [q for q in qlist if q["correct"] == "B"],
            "C": [q for q in qlist if q["correct"] == "C"],
        }

        def least_used_letter(counts_dict):
            return min(("A", "B", "C"), key=lambda k: counts_dict[k])

        for letter in ("A", "B", "C"):
            while counts[letter] > target and groups[letter]:
                q = groups[letter].pop()
                counts[letter] -= 1

                new_letter = least_used_letter(counts)
                counts[new_letter] += 1

                # Swap the answers so that the correct answer moves to new_letter
                if letter != new_letter:
                    temp = q[f"answer_{letter.lower()}"]
                    q[f"answer_{letter.lower()}"] = q[f"answer_{new_letter.lower()}"]
                    q[f"answer_{new_letter.lower()}"] = temp

                q["correct"] = new_letter

        print("  nachher:", counts)

    return balanced

# ------------------------------------------------------------
# Neue Datei schreiben
# ------------------------------------------------------------
def write_output(original_content, questions, filename):
    lines = []
    lines.append("quiz_question_t quiz_questions[] = {\n")
    for q in questions:
        line = (
            f'    {{ "{q["question"]}", '
            f'"{q["answer_a"]}", '
            f'"{q["answer_b"]}", '
            f'"{q["answer_c"]}", '
            f'\'{q["correct"]}\', '
            f'\'{q["difficulty"]}\', '
            f'{q["category"]}, '
            f'"{q["correct_reaction"]}", '
            f'"{q["wrong_reaction"]}" }},\n'
        )
        lines.append(line)
    lines.append("};")

    new_array = "".join(lines)

    new_content = re.sub(
        r"quiz_question_t\s+quiz_questions\s*\[\]\s*=\s*\{.*?\};",
        new_array,
        original_content,
        flags=re.DOTALL,
    )

    with open(filename, "w", encoding="utf-8") as f:
        f.write(new_content)

    print(f"\nNeue Datei geschrieben: {filename}")


# ------------------------------------------------------------
# JSON Import und Export
# ------------------------------------------------------------

def export_json(questions, filename):
    with open(filename, "w", encoding="utf-8") as f:
        json.dump(questions, f, indent=4, ensure_ascii=False)
    print(f"JSON exportiert nach: {filename}")


def import_json(filename):
    with open(filename, "r", encoding="utf-8") as f:
        data = json.load(f)
    print(f"JSON importiert aus: {filename}")
    return data


# ------------------------------------------------------------
# Excel Import und Export
# ------------------------------------------------------------

def export_excel(questions, filename):
    try:
        import pandas as pd
    except ImportError:
        print("Pandas ist nicht installiert. Excel-Export nicht möglich.")
        return

    df = pd.DataFrame(questions)
    df.to_excel(filename, index=False)
    print(f"Excel exportiert nach: {filename}")


def import_excel(filename):
    try:
        import pandas as pd
    except ImportError:
        print("Pandas ist nicht installiert. Excel-Import nicht möglich.")
        return []

    df = pd.read_excel(filename)
    print(f"Excel importiert aus: {filename}")
    return df.to_dict(orient="records")


# ------------------------------------------------------------
# Hauptprogramm
# ------------------------------------------------------------
if __name__ == "__main__":
    original = None
    questions = None

    while True:
        print("\nOptionen:")
        print("1 = Header einlesen")
        print("2 = Header schreiben")
        print("3 = Antworten ausbalancieren")
        print("4 = Export JSON")
        print("5 = Export Excel")
        print("6 = Import JSON")
        print("7 = Import Excel")
        print("8 = Beenden")

        choice = input("Auswahl: ").strip()

        if choice == "1":
            questions, original = parse_quiz_data(HEADER_FILE)
            print(f"{len(questions)} Fragen eingelesen.")
            per_cat = count_correct_per_category(questions)
            print("\nVerteilung je Kategorie:")
            for cat, cnt in per_cat.items():
                print(f"{cat}: {cnt}")

        elif choice == "2":
            if questions is not None:
                write_output(original, questions, OUTPUT_FILE)

        elif choice == "3":
            questions = balance_per_category(questions)
            print("\nVerteilung je Kategorie:")
            per_cat = count_correct_per_category(questions)
            for cat, cnt in per_cat.items():
                print(f"  {cat}: {cnt}")

        elif choice == "4":
            export_json(questions, "quiz_export.json")

        elif choice == "5":
            export_excel(questions, "quiz_export.xlsx")

        elif choice == "6":
            questions = import_json("quiz_export.json")

        elif choice == "7":
            questions = import_excel("quiz_export.xlsx")

        elif choice == "8":
            print("Beendet.")
            exit()
