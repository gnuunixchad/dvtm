static unsigned int
get_occupied_tags(void)
{
	unsigned int occupied = 0;
	Client *c;
	for (c = clients; c; c = c->next)
		occupied |= c->tags;
	return occupied & TAGMASK;
}

static unsigned int
rotate_tags(unsigned int tags_mask, int direction, bool skip_unoccupied, bool skip_occupied)
{
	unsigned int occupied = get_occupied_tags();
	unsigned int result = 0;
	int i, tag_count = sizeof(tags) / sizeof(tags[0]);

	if (!skip_unoccupied && !skip_occupied) {
		if (direction > 0) {
			result = (tags_mask << 1) | (tags_mask >> (tag_count - 1));
		} else {
			result = (tags_mask >> 1) | (tags_mask << (tag_count - 1));
		}
		return result & TAGMASK;
	}

	for (i = 0; i < tag_count; i++) {
		unsigned int tag_bit = 1 << i;
		if (tags_mask & tag_bit) {
			unsigned int test_bit = tag_bit;
			unsigned int found = 0;
			int count = 0;

			do {
				if (direction > 0) {
					if (test_bit << 1 && (test_bit << 1) <= TAGMASK)
						test_bit = test_bit << 1;
					else
						test_bit = 1;
				} else {
					if (test_bit >> 1)
						test_bit = test_bit >> 1;
					else
						test_bit = 1 << (tag_count - 1);
				}

				int is_occupied = (occupied & test_bit) != 0;
				int should_select = (skip_unoccupied && is_occupied) ||
									(skip_occupied && !is_occupied);

				if (should_select) {
					result |= test_bit;
					found = 1;
					break;
				}
				count++;
			} while (test_bit != tag_bit && count < tag_count);

			if (!found)
				result |= tag_bit;
		}
	}

	return result;
}

static void
shifttag_with_filter(const char *args[], bool skip_unoccupied, bool skip_occupied)
{
	if (!args || !args[0])
		return;

	int direction = atoi(args[0]);
	unsigned int occupied = get_occupied_tags();

	if (skip_unoccupied && !skip_occupied && occupied == 0)
		return;
	if (skip_occupied && !skip_unoccupied && (occupied == TAGMASK))
		return;

	static unsigned int current_tags = 1;


	unsigned int nextseltags = rotate_tags(current_tags, direction, skip_unoccupied, skip_occupied);

	if (nextseltags != current_tags) {
		int i;
		for (i = 0; i < LENGTH(tags); i++) {
			if (nextseltags & (1 << i)) {
				const char *newargs[] = { tags[i], NULL };
				view(newargs);
				current_tags = nextseltags;
				break;
			}
		}
	}
}

void
shifttag(const char *args[])
{
	shifttag_with_filter(args, false, false);
}

void
shifttag_occupied(const char *args[])
{
	shifttag_with_filter(args, true, false);
}

void
shifttag_unoccupied(const char *args[])
{
	shifttag_with_filter(args, false, true);
}
