class IterableStructure:
    def __init__(self):
        self.iterable_data = []
        self.index = -1

    def __iter__(self):
        return iter(self.iterable_data)

    def __next__(self):
        if self.index == len(self.iterable_data) - 1:
            raise StopIteration
        else:
            self.index += 1
        return self.iterable_data[self.index]

    def __len__(self):
        return len(self.iterable_data)

    def __setitem__(self, index, value):
        self.iterable_data[index] = value

    def __getitem__(self, index):
        return self.iterable_data[index]

    def __delitem__(self, index):

        del self.iterable_data[index]

    def append(self, element):
        self.iterable_data.append(element)

    def remove(self, element):
        self.iterable_data.remove(element)

    def pop(self):
        self.iterable_data.pop()

    @staticmethod
    def filter(list_to_filter, function):
        filtered_list = []
        for element in list_to_filter:
            if function(element) is True:
                filtered_list.append(element)
        return filtered_list

    @staticmethod
    def gnome_sort(list, function):
        """
        GNOME SORT FUNCTION
        This sorting method is also called the Stupid sort and it is based on the concept of a Garden Gnome
        sorting his flower pots(He looks at the flower pot next to him and the previous one; if they are in the right
        order he steps one pot forward, otherwise he swaps them and steps one pot backwards. If there is no previous pot
        (he is at the starting of the pot line), he steps forwards; if there is no pot next to him (he is at the end of
        the pot line), he is done.
        The steps are the following:
        -> if the position is 0, we go to the next position (and element)
        -> in the case when the position is not 0, if the current element and the previous one check the condition,
        we go to the next position because we don't have to perform any sorting with the current element and the
        previous one
        -> in this case, as the function is really general, the comparison between the elements is done with a
        comparison function, but the code can be simplified by using inequalities and equalities directly in the elif
        branch
        -> if the elements do not check the condition,we swap them and decrement the index, because now we have to check
        if the element that is now on the previous position and the element that is before it check the condition or not
        -> as we can see,in the gnome sort method the index isn't always incremented or decremented, its value is
        modified based on the branch that the function enters
        -> the program stops if the index is equal with the length of the list, which means that we reached the end of
        the list and we should have o sorted list at the end.

        """
        index = 0
        length = len(list)
        while index < length:
            if index == 0:
                index = index + 1
            elif function(list[index], list[index - 1]) is True:
                index = index + 1
            else:
                list[index], list[index-1] = list[index-1], list[index]
                index = index - 1
        return list

