with open('check_result', 'w', encoding='utf-8') as output:
    with open('answer', 'r', encoding='utf-16') as answer:
        with open('my_answer', 'r', encoding='utf-16') as my_answer:
            i = 1
            for (line_ans, line_my) in (zip(answer, my_answer)):
                if line_ans != line_my:
                    print(f"line {i}:\n\tcorrect: {line_ans}my answer: {line_my}")
                i += 1