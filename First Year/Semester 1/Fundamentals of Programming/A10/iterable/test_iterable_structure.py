import unittest

from src.iterable.iterable_structure import IterableStructure


class TestIterableModule(unittest.TestCase):
    def test_class(self):
        my_list = IterableStructure()
        my_list.append(1)
        my_list.append(7)
        my_list.append(0)
        my_list.append(3)
        my_iter = my_list.__iter__()
        self.assertEqual(my_list.__next__(), 1)
        self.assertEqual(my_list.__next__(), 7)
        self.assertEqual(my_list.__next__(), 0)
        self.assertEqual(my_list.__next__(), 3)
        self.assertRaises(StopIteration, next, my_list)
        self.assertEqual(len(my_list), 4)
        my_list.remove(3)
        self.assertEqual(len(my_list), 3)
        my_list.__setitem__(0, 4)
        self.assertEqual(my_list[0], 4)
        my_list.append(3)
        self.assertEqual(len(my_list), 4)
        my_list.__delitem__(3)
        self.assertEqual(len(my_list), 3)
        my_list.pop()
        self.assertEqual(len(my_list), 2)

    def test_filter(self):
        letters = ['a', 'b', 'd', 'e', 'i', 'j', 'o']
        def filterVowels(letter):
            vowels = ['a', 'e', 'i', 'o', 'u']

            if (letter in vowels):
                return True
            else:
                return False
        filteredVowels = IterableStructure.filter(letters, filterVowels)
        self.assertEqual(len(filteredVowels), 4)

    def test_gnome_sort(self):
        list = [ 34, 2, 10, -9]

        def compare_elements(elem1, elem2):
            if float(elem1) >= float(elem2):
                return True
            else:
                return False

        sorted_list = IterableStructure.gnome_sort(list, compare_elements)
        self.assertEqual(len(sorted_list), 4)
        self.assertEqual(sorted_list[0], -9)
        self.assertEqual(sorted_list[1], 2)
        self.assertEqual(sorted_list[2], 10)
        self.assertEqual(sorted_list[3], 34)
