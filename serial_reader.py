import serial
import csv 
sample_duration_s = 60
filename = "test-sin.csv"
encoding = 'utf-8'
ser = serial.Serial('COM3', 115200, timeout=1)
sample_count = 0

with open(filename, 'w') as csvfile:
    csvwriter = csv.writer(csvfile)

    while sample_count < 1000*sample_duration_s:
        # Read in a new line over serial
        new_line = ser.readline()
        # Remove the return and new line characters at the end
        cleaned_line = str(new_line[:-2], encoding)
        # Conver the string into a list of floats
        my_flts = [float(x) for x in cleaned_line.split(",")]
        print(my_flts)
        # Write that list of floats to the CSV as data
        csvwriter.writerow(my_flts)
        sample_count += 1
    
    ser.close()