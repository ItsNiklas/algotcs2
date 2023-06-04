import random
import logging
from typing import List

logging.basicConfig(level=logging.DEBUG)


def generate_random_array(
    size: int, low: int = -(10**6), high: int = 10**6
) -> List[int]:
    return [random.randint(low, high) for _ in range(size)]


def is_guess_correct(arr: List[int], guess: List[int]) -> bool:
    return arr == guess


def solve(arr: List[int], q: str):
    guess = list(map(int, q.split(" ")[1:]))
    if is_guess_correct(arr, guess):
        raise SystemExit("Guess is correct.")
    else:
        raise SystemExit("Guess is incorrect.")


def main(N: int = 8):
    k = random.randint(1, N - 1)
    print(N, k)

    arr = generate_random_array(N, -(10**2), 10**2)
    logging.debug(f"Alice's array: {arr}")

    for _ in range(N):
        q = input()

        if q[0] == "!":
            solve(arr, q)

        q_splitted = q.split(" ")
        if len(q_splitted) != k + 1:
            raise SystemExit("Invalid question length.")

        print(sum(arr[int(i) - 1] for i in q_splitted[1:]), flush=True)

    solve(arr, input())


if __name__ == "__main__":
    main()
