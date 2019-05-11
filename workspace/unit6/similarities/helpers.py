from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    lines_a = a.split("\n")
    lines_b = b.split("\n")
    linesSimilar = list()
    for line1 in lines_a:
        for line2 in lines_b:
            if line1.strip("\n") == line2.strip("\n") and line1.strip("\n") not in linesSimilar:
                linesSimilar.append(line1.strip("\n"))
    return linesSimilar


def sentences(a, b):
    """Return sentences in both a and b"""

    lines_a = a.split("\n")
    lines_b = b.split("\n")
    sent1 = list()
    sent2 = list()
    sentSimilarities = list()

    for line in lines_a:
        temp = sent_tokenize(line)  # sent_tokenize from the Natural Language Toolkit to "tokenize" (i.e., separate) each string into a list of sentences
        for sentence in temp:
            if sentence not in sent1:
                sent1.append(sentence)
    for line in lines_b:
        temp = sent_tokenize(line)
        for sentence in temp:
            if sentence not in sent2:
                sent2.append(sentence)
    for sentence1 in sent1:
        for sentence2 in sent2:
            if sentence1 == sentence2 and sentence1 not in sentSimilarities:
                sentSimilarities.append(sentence1)
    return sentSimilarities


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    lines_a = a.split("\n")
    lines_b = b.split("\n")
    substrSimilarities = list()
    substrings1 = list()
    substrings2 = list()

    for line in lines_a:
        temp = sent_tokenize(line)
        for sentence in temp:
            x = len(sentence)
            for i in range(x):
                if (i + n) <= x:
                    if sentence[i: i + n] not in substrings1:
                        substrings1.append(sentence[i: i + n])
    for line in lines_b:
        temp = sent_tokenize(line)
        for sentence in temp:
            x = len(sentence)
            for i in range(x):
                if (i + n) <= x:
                    if sentence[i: i + n] not in substrings2:
                        substrings2.append(sentence[i: i + n])
    for substr in substrings2:
        if (substr in substrings1) and (substr not in substrSimilarities):
            substrSimilarities.append(substr)
    return substrSimilarities

