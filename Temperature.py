# Estevan Cisneros
# Week 09: Homework 6
# Program that uses a list to store daily temperatures (in Fahrenheit) and then performs statistical analysis on the values.

###########################################################
##### DO NOT ALTER OR DELETE ANY OF THE EXISTING CODE #####
###########################################################

######## Function definitions ########

# Function 1 definition: get integer value from user
# and return the value to the main function.
def get_temp():
    temperature: int  # temperature entered by user
    temperature = int(input("Enter temperature (\u00b0F): "))
    return temperature

# Function 2 definition: accepts the sum and count of all temperatures
# and returns the average temperature.
def calculate_average(sum: int, count: int):
    average: float  # average temperature
    if count > 0:
        average = sum / count
        return average

#####################################
###### Begin mainline function ######
#####################################

# Declare/initialize variables using type hinting
temperature: int  # temperature to be added to a list of temps
temp_list: list = []  # initialize an empty list to store all temps
temp_index: int = 0  # loop control variable
temp_count: int  # number of temperatures to be entered
temp_sum: int = 0  # sum of all temperatures (currently is 0)
temp_average: float  # stores the calculated average temperature

normal: int = 0  # number of normal
caution: int = 0  # number of caution
extreme_caution: int = 0  # number of extreme caution
danger: int = 0  # number of danger
extreme_danger: int = 0  # number of extreme danger

# Prompt the user for the number of temperatures to be entered.
temp_count = int(input("How many temperatures? "))

# Counter-controlled loop (how many times will it run?)
while temp_index < temp_count:
    temperature = get_temp()  # Call get_temp() function and store return value in temperature variable
    temp_list.append(temperature)  # Append the new temperature to the list of temperatures
    temp_sum += temperature  # Update the sum of temperatures
    temp_index += 1  # Increment loop control variable

# Blank line for spacing
print()

# Calculate and print average temperature
if temp_count > 0:
    temp_average = calculate_average(temp_sum, temp_count)  # Call Function 2 and store return value in temp_average
    print("Average temp: {:.1f}\u00b0F".format(temp_average))  # Print the average of temperatures.
else:
    print("Average temp: none")  # Print a different message (see Sample Runs)

# Counter-controlled loop to loop through the list of temperatures
temp_index = 0  # set temp_index back to 0
while temp_index < temp_count:
    current_temp = temp_list[temp_index]
    if current_temp < 80:
        normal += 1
    elif 80 <= current_temp <= 89:
        caution += 1
    elif 90 <= current_temp <= 105:
        extreme_caution += 1
    elif 106 <= current_temp <= 129:
        danger += 1
    else:  # current_temp > 129
        extreme_danger += 1
    temp_index += 1

# Print the totals with appropriate labels and formatting
print("\nNumber of Normal:", normal)
print("Number of Caution:", caution)
print("Number of Extreme Caution:", extreme_caution)
print("Number of Danger:", danger)
print("Number of Extreme Danger:", extreme_danger)