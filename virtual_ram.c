#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// LRU page replacement algorithm
int LRU(int *reference_string, int size, int frame_count)
{
    int page_faults = 0;
    int *frame_buffer = (int *)malloc(frame_count * sizeof(int));
    int *time_stamps = (int *)malloc(frame_count * sizeof(int));

    for (int i = 0; i < frame_count; i++)
    {
        frame_buffer[i] = -1;
        time_stamps[i] = -1;
    }

    for (int i = 0; i < size; i++)
    {
        int page_to_replace = -1;
        int page_in_buffer = 0;
        int oldest_time_stamp = -1;

        // check if page is already in buffer
        for (int j = 0; j < frame_count; j++)
        {
            if (frame_buffer[j] == reference_string[i])
            {
                page_in_buffer = 1;
                time_stamps[j] = i;
                break;
            }
        }

        // if page is not in buffer, increment page faults and add page to buffer
        if (!page_in_buffer)
        {
            page_faults++;

            // find page to replace using LRU algorithm
            for (int j = 0; j < frame_count; j++)
            {
                if (time_stamps[j] == -1)
                {
                    page_to_replace = j;
                    break;
                }
                else if (time_stamps[j] > oldest_time_stamp)
                {
                    oldest_time_stamp = time_stamps[j];
                    page_to_replace = j;
                }
            }

            frame_buffer[page_to_replace] = reference_string[i];
            time_stamps[page_to_replace] = i;
        }
    }

    free(frame_buffer);
    free(time_stamps);
    return page_faults;
}

// FIFO page replacement algorithm
int FIFO(int *reference_string, int size, int frame_count)
{
    int page_faults = 0;
    int *frame_buffer = (int *)malloc(frame_count * sizeof(int));
    int buffer_pointer = 0;

    for (int i = 0; i < size; i++)
    {
        int page_to_replace = -1;
        int page_in_buffer = 0;

        // check if page is already in buffer
        for (int j = 0; j < frame_count; j++)
        {
            if (frame_buffer[j] == reference_string[i])
            {
                page_in_buffer = 1;
                break;
            }
        }

        // if page is not in buffer, increment page faults and add page to buffer
        if (!page_in_buffer)
        {
            page_faults++;

            if (frame_buffer[buffer_pointer] != -1)
            {
                page_to_replace = buffer_pointer;
            }

            frame_buffer[buffer_pointer] = reference_string[i];
            buffer_pointer = (buffer_pointer + 1) % frame_count;
        }
    }

    free(frame_buffer);
    return page_faults;
}

// OPT page replacement algorithm
int OPT(int *reference_string, int size, int frame_count)
{
    int page_faults = 0;
    int *frame_buffer = (int *)malloc(frame_count * sizeof(int));

    for (int i = 0; i < frame_count; i++)
    {
        frame_buffer[i] = -1;
    }

    for (int i = 0; i < size; i++)
    {
        int page_to_replace = -1;
        int page_in_buffer = 0;
        int max_distance = -1;

        // check if page is already in buffer
        for (int j = 0; j < frame_count; j++)
        {
            if (frame_buffer[j] == reference_string[i])
            {
                page_in_buffer = 1;
                break;
            }
        }

        // if page is not in buffer, increment page faults and add page to buffer
        if (!page_in_buffer)
        {
            page_faults++;

            // find page to replace using OPT algorithm
            for (int j = 0; j < frame_count; j++)
            {
                if (frame_buffer[j] == -1)
                {
                    page_to_replace = j;
                    break;
                }
                else
                {
                    int distance = 0;
                    for (int k = i; k < size; k++)
                    {
                        if (reference_string[k] == frame_buffer[j])
                        {
                            distance = k - i;
                            break;
                        }
                    }

                    if (distance > max_distance)
                    {
                        max_distance = distance;
                        page_to_replace = j;
                    }
                }
            }

            frame_buffer[page_to_replace] = reference_string[i];
        }
    }

    free(frame_buffer);
    return page_faults;
}

// create a random page reference string
void create_ref_str(int *reference_string, int size)
{
    for (int i = 0; i < size; i++)
    {
        reference_string[i] = rand() % 10; // page numbers range from 0 to 9
    }
}

int main()
{
    srand(time(NULL));

    int reference_string_size;
    printf("Enter the size of the reference string: ");
    scanf("%d", &reference_string_size);

    int *reference_string = (int *)malloc(reference_string_size * sizeof(int));
    create_ref_str(reference_string, reference_string_size);

    int frame_count;
    printf("Enter the number of page frames: ");
    scanf("%d", &frame_count);

    int LRU_page_faults = LRU(reference_string, reference_string_size, frame_count);
    int FIFO_page_faults = FIFO(reference_string, reference_string_size, frame_count);
    int OPT_page_faults = OPT(reference_string, reference_string_size, frame_count);

    printf("LRU page faults: %d\n", LRU_page_faults);
    printf("FIFO page faults: %d\n", FIFO_page_faults);
    printf("OPT page faults: %d\n", OPT_page_faults);

    free(reference_string);
    return 0;
}
