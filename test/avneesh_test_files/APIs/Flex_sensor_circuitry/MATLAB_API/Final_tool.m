% Author: Avneesh Mishra
% Purpose: To get the resistance values to be used for flex sensor
% circuitry. This tool essentially gives you all the resistance values to
% be used in the circuit implementation for the best results.
% Instruction to use:
%    If you're freshly getting values, create resistor_vals.mat and
%    sensor_readings.mat matrices 

%% Setup section
clc;clearvars;close all;

%% Data initialization
fprintf("======= Initializing the system ======= \n");
try
    fprintf("Trying to read the files :\n");
    fprintf("- resistor_vals.mat: For resistance values in variable 'resistor_values'\n");
    fprintf("- sensor_readings.mat: For 'flex_sizes', 'finger_names', 'supply_voltage', 'adc_max_input', 'full_in_flex' and 'full_out_flex'\n");
    load sensor_readings.mat
    flex_sizes;
    finger_names;
    supply_voltage;
    adc_max_input;
    full_out_flex;
    full_in_flex;
    load resistor_vals.mat
    resistor_values;
    % reload_values;   % Uncomment this for the default to be restored
catch
    fprintf("\tData not found \nInitializing fresh data...\n");
    % Default values: List of measurements: Data loading section
    flex_sizes = {
        '2.2"'
        '4.5"'
        };
    finger_names = [
        "Thumb"
        "Index Finger"
        ];
    full_out_flex = [
        132
        7.5
        ];
    full_in_flex = [
        73
        26
        ];
    supply_voltage = 5;
    adc_max_input = 4.95;
    resistor_values = [1 1.5 2.2 3.3 4.7 5.6 6.8 8.2 10 15 22 33 47 56 68 100 150 220 330 470]';
    save sensor_readings.mat finger_names flex_sizes full_in_flex full_out_flex supply_voltage adc_max_input;
    save resistor_vals.mat resistor_values;
    fprintf("Data initialized and saved\n");
end
% Show everything as tables
col_names = {'finger_name', 'flex_sensor_size', 'flex_in_kohm', 'flex_out_kohm'};
input_table = table(finger_names, flex_sizes, full_in_flex, full_out_flex);
input_table.Properties.VariableNames = col_names;
% List of resistance values in k ohm
resistor_table = table(resistor_values, 'VariableNames', {'Resistance_kohm'});
fprintf("The voltage supply is %f V to 0 V\n", supply_voltage);
fprintf("The ADC input voltage range is %f V to 0 V\n", adc_max_input);
fprintf("The resistance values available are the following (everything in kΩ)\n");
disp(resistor_table);
fprintf("Data values (all resistances in kΩ)\n");
disp(input_table);

%% Data calculations - Voltage divider
fprintf("======= Voltage divider analysis ========\n");
fprintf("The flex sensors are either 'above' or 'below' in the voltage divider\n");
above_position = [];   % 1 for above 0 for below
r1_vals = [];          % Companion resistor R1 (in k ohm)
v_max = [];            % Maximum voltage
v_min = [];            % Minimum voltage
v_dev = [];            % Deviation voltage
vs = supply_voltage;
for i = 1:length(finger_names)
    fprintf("# Analying finger %d - %s\n", i, finger_names(i));
    % Check if sensor must be 'above' or 'below'
    if full_in_flex(i) > full_out_flex(i)
        % Resistance is greater when we flex inwards, we need the voltage
        % to increase when we flex inwards. Positioning the sensor 'below' 
        % in the voltage divider does the work.
        fprintf("Flex in resistance is greater, resistance increases while bending inwards, flex sensor 'below'\n");
        above_position(length(above_position) + 1, 1) = 0;
        % functions
        min_r = full_out_flex(i);
        max_r = full_in_flex(i);
        min_v = @(res) vs * min_r / (min_r + res);
        max_v = @(res) vs * max_r / (max_r + res);
        dev_rg = @(res) vs * (max_r/(max_r + res) - min_r/(min_r + res));
        fprintf("Deviation in voltage range: \n");
        disp(dev_rg);
    else
        % Resistance is greater when we flex outwards, we need the voltage
        % to increase when we flex inwards. Positioning the sensor 'above' 
        % in the voltage divider does the work.
        fprintf("Flex out resistance is greater, resistance decreases while bending inwards, flex sensor 'above'\n");
        above_position(length(above_position) + 1, 1) = 1;
        min_r = full_in_flex(i);
        max_r = full_out_flex(i);
        min_v = @(res) vs * res / (max_r + res);
        max_v = @(res) vs * res / (min_r + res);
        dev_rg = @(res) vs * (res/(min_r + res) - res/(max_r + res));
        fprintf("Deviation in voltage range: \n");
        disp(dev_rg);
    end
    % Select the best companion resistor
    dev_vals = arrayfun(@(r) dev_rg(r), resistor_values);
    [best_dev, index_res] = max(dev_vals);
    r1_vals(length(r1_vals) + 1, 1) = resistor_values(index_res);
    % Voltage assignments
    v_dev(length(v_dev) + 1, 1) = best_dev;
    v_min(length(v_min) + 1, 1) = min_v(resistor_values(index_res));
    v_max(length(v_max) + 1, 1) = max_v(resistor_values(index_res));
end
input_table.above_pos = above_position;
input_table1 = input_table;
input_table1.r1_vals = r1_vals;
input_table1.Properties.VariableNames{6} = 'r1_kohm';
input_table1.min_v_raw = v_min;
input_table1.max_v_raw = v_max;
input_table1.dev_v_raw = v_dev;
fprintf("Data values (all resistances in kΩ)\n");
disp(input_table1);

%% Data calculations - Wheatstone bridge
fprintf("======= Wheatstone bridge side arm analysis ========\n");
min_v = min(v_min);
fprintf("Minimum voltage in the main arm is %f V\n", min_v);
vlt_out = @(r_up, r_dw) vs * r_dw / (r_up + r_dw);
fprintf("Voltage divider equation is: \n");
disp(vlt_out);
% We need to find the resistance combination that'll give us a voltage just
% lesser than min_v (because then we can make the reference in +ve only).
vlt_vals = []; % 2D Voltage matrix. First index -> upper resistance, second index -> lower resistance
for i = 1:length(resistor_values)
    for j = 1:length(resistor_values)
        vlt_vals(i, j) = vlt_out(resistor_values(i), resistor_values(j));
    end
end
vlt_dev = min_v - vlt_vals; % Voltage deviations (vlt_vals must be just lesser than min_v)
vlt_dev(vlt_dev < 0) = NaN; % We don't need the places where vlt_vals > min_v
lowest_v = min(vlt_dev(:));
[up_index, dw_index] = find(vlt_dev == lowest_v, 1, 'last');
rside_upper = resistor_values(up_index);
rside_lower = resistor_values(dw_index);
fprintf("Best resistor pairs found\n");
fprintf("Upper resistance R3 = %f kΩ and lower resistance R4 = %f kΩ\n", rside_upper, rside_lower);
best_v = vlt_vals(up_index, dw_index);
fprintf("Voltage due to this is %f V\n", best_v);
effect_wb = 100 * best_v/min_v;
fprintf("Effectiveness = %f %% \n", effect_wb);
input_table2 = input_table;
input_table2.min_dv = v_min - best_v;
input_table2.max_dv = v_max - best_v;
input_table2.dev_dv = input_table2.max_dv - input_table2.min_dv;
input_table2.flex_in_kohm = [];
input_table2.flex_out_kohm = [];
fprintf("Data values (all resistances in kΩ)\n");
fprintf("dv -> Differential Voltage\n");
disp(input_table2);

%% Data calculations - Instrumentation Amplifier
fprintf("======= Instrumentation Amplifier analysis ========\n");
max_out = adc_max_input;
fprintf("The maximum output range is 0 V to %f V\n", max_out);
max_dv = max(input_table2.max_dv);
fprintf("The maximum possible differential input voltage is %f V\n", max_dv);
% The max_dv at input must give max_out at output
desired_gain = max_out / max_dv; % Desired gain
fprintf("The desired gain is %f\n", desired_gain);
calc_gain = @(r_f, r_b) r_f / r_b;
gain_values = []; % 2D gain matrix, first index is forward resistor and second index is back resistor
for i = 1:length(resistor_values)
    for j = 1:length(resistor_values)
        gain_values(i,j) = calc_gain(resistor_values(i), resistor_values(j));
    end
end
gain_dev = desired_gain - gain_values; % Get the value and index with gain_values just lesser than desired_gain
gain_dev(gain_dev < 0) = NaN;  % We don't need gain_values > desired_gain
best_gain_dev = min(gain_dev(:));
[fw_index, bw_index] = find(gain_dev == best_gain_dev, 1, 'last');
best_gain = gain_values(fw_index, bw_index);
res_f = resistor_values(fw_index);
res_b = resistor_values(bw_index);
fprintf("The resistors chosen are Rf = %f kΩ and Rb = %f kΩ\n", res_f, res_b);
fprintf("Giving a gain of %f = (Rf / Rb) \n", best_gain);
effect_ia = 100 * best_gain / desired_gain;
fprintf("Effectiveness = %f %% \n", effect_ia);
input_table3 = input_table2;
input_table3.min_v3 = input_table2.min_dv * best_gain;
input_table3.max_v3 = input_table2.max_dv * best_gain;
input_table3.dev_v3 = input_table3.max_v3 - input_table3.min_v3;
fprintf("Data values (all resistances in kΩ)\n");
fprintf("v3 -> output voltage of the entire circuitry \n");
disp(input_table3);


%% Final results
% Display everything
fprintf("\n\n==================== FINAL RESULTS ====================\n");
fprintf("Data values (all resistances in kΩ)\n");
fprintf("R1 -> Resistor in the same arm as the sensor, in kΩ\n");
fprintf("v1 -> Raw voltage (of the voltage divider), in V\n");
fprintf("v2 -> Output of differential voltage from wheatstone bridge, in V\n");
fprintf("v3 -> Output of instrumentation amplifier (final output), in V\n");
output_table = input_table;
above_pos_vals = output_table.above_pos;
above_str = [];
for i = 1:length(above_pos_vals)
    if (above_pos_vals(i) == 1)
        above_str = [above_str; "above"];
    else
        above_str = [above_str; "below"];
    end
end
output_table.above_pos = above_str;
output_table.r1_kohm = r1_vals;
output_table.min_v1 = v_min;
output_table.max_v1 = v_max;
output_table.del_v1 = output_table.max_v1 - output_table.min_v1;
output_table.min_v2 = input_table2.min_dv;
output_table.max_v2 = input_table2.max_dv;
output_table.del_v2 = output_table.max_v2 - output_table.min_v2;
output_table.min_v3 = input_table3.min_v3;
output_table.max_v3 = input_table3.max_v3;
output_table.del_v3 = output_table.max_v3 - output_table.min_v3;
fprintf("All details here\n");
disp(output_table);
fprintf("Breif here\n");
final_output_table = output_table;
final_output_table.min_v1 = [];
final_output_table.max_v1 = [];
final_output_table.del_v1 = [];
final_output_table.min_v2 = [];
final_output_table.max_v2 = [];
final_output_table.del_v2 = [];
% final_output_table.Properties.RowNames = flex_sizes;
disp(final_output_table);
fprintf("Side arm resistances: \n");
fprintf("\tUpper (R3) = %f kΩ \n\tLower (R4) = %f kΩ\n", rside_upper, rside_lower);
fprintf("\tEffectiveness = %f %%\n", effect_wb);
fprintf("Instrumentation amplifier reistances: \n");
fprintf("\tForward resistance (Rf) = %f kΩ \n\tBackward resistance (Rb) = %f kΩ\n", res_f, res_b);
fprintf("\tEffectiveness = %f %%\n", effect_ia);
fprintf("Total effectiveness = %f %%\n", effect_ia * effect_wb / 100);
