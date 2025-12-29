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
        print("  Vorher:", counts)
        print("  Ziel je Buchstabe:", target)

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

        print("  Nachher:", counts)

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
# Hauptprogramm
# ------------------------------------------------------------
if __name__ == "__main__":
    questions, original = parse_quiz_data(HEADER_FILE)

    print("\nVerteilung je Kategorie (vorher):")
    per_cat = count_correct_per_category(questions)
    for cat, cnt in per_cat.items():
        print(f"  {cat}: {cnt}")

    choice = input("\nInnerhalb jeder Kategorie ausbalancieren? (j/n): ").strip().lower()

    if choice == "j":
        balanced = balance_per_category(questions)

        print("\nVerteilung je Kategorie (nachher):")
        per_cat = count_correct_per_category(balanced)
        for cat, cnt in per_cat.items():
            print(f"  {cat}: {cnt}")

        write_output(original, balanced, OUTPUT_FILE)
    else:
        print("Keine Änderungen vorgenommen.")
