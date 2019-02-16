%% Setup section
clc;clearvars;close all;
%% Default configurations
V_supply = 5;
fprintf("Supply voltage is %f V\n", V_supply);
fprintf("Resistor values in 'resistor_values' (all in kΩ)\n");
% List of resistance values in k ohm
resistor_values = [1 1.5 2.2 3.3 4.7 5.6 6.8 8.2 10 15 22 33 47 56 68 100 150 220 330 470];
%% 2.2 inch Flex Sensor
fprintf("\n==== Checking diagnostics for 2.2 inch Flex Sensor ====\n");
min_R1 = 73;    % clentched in
max_R1 = 132;   % clentched out
fprintf("Full in: %f kΩ, Full out: %f kΩ\n", min_R1, max_R1);
res_range = @(x) V_supply * (x/(x+min_R1) - x/(x+max_R1));
dev_values1 = arrayfun(res_range, resistor_values);
[md1, mi1] = max(dev_values1);
fprintf("Maximum value for voltage deviation is %f V, index is %d\n", md1, mi1);
fprintf("Resistance value suggested is %f kΩ\n", resistor_values(mi1));
fprintf("Attach the resistor to the bottom part of voltage divider and flex sensor to top\n");
min_V1 = V_supply * resistor_values(mi1)/(resistor_values(mi1) + max_R1);
fprintf("Minimum voltage reading (max outwards): %f V\n", min_V1);
max_V1 = V_supply * resistor_values(mi1)/(resistor_values(mi1) + min_R1);
fprintf("Maximum voltage reading (max inwards): %f V\n", max_V1);
%% 4.5 inch Flex Sensor
fprintf("\n==== Checking diagnostics for 4.5 inch Flex Sensor ====\n");
fprintf("Resistor values are same as above stated\n");
min_R2 = 7.5;     % out
max_R2 = 26;      % in
fprintf("Full in: %f kΩ, Full out: %f kΩ\n", max_R2, min_R2);
res_range = @(x) V_supply * (max_R2/(max_R2 + x) - min_R2/(min_R2 + x));
dev_values2 = arrayfun(res_range, resistor_values);
[md2, mi2] = max(dev_values2);
fprintf("Maximum value for voltage deviation is %f V, index is %d\n", md2, mi2);
fprintf("Resistance value suggested is %f kΩ\n", resistor_values(mi2));
fprintf("Attach the resistor to the upper part of voltage divider and flex sensor to bottom\n");
min_V2 = V_supply * min_R2 / (min_R2 + resistor_values(mi2));
fprintf("Minimum voltage reading (max outwards): %f V\n", min_V2);
max_V2 = V_supply * max_R2 / (max_R2 + resistor_values(mi2));
fprintf("Maximum voltage reading (max inwards): %f V\n", max_V2);
%% Side arm analysis
fprintf("\n==== Voltage analysis ====\n");
[min_V, min_Vi] = min([min_V1 min_V2]);
fprintf("Minimum voltage: %f V, index: %i\n", min_V, min_Vi);
% Voltage deviations
min_dV1 = min_V1 - min_V;
max_dV1 = max_V1 - min_V;
delta_V1 = max_dV1 - min_dV1;
min_dV2 = min_V2 - min_V;
max_dV2 = max_V2 - min_V;
delta_V2 = max_dV2 - min_dV2;
fprintf("Deviation on 2.2 inch flex sensor: %f V to %f V [%f V] (ideal)\n", min_dV1, max_dV1, delta_V1);
fprintf("Deviation on 4.5 inch flex sensor: %f V to %f V [%f V] (ideal)\n", min_dV2, max_dV2, delta_V2);
% Generate the resistor divider matrix
resistor_div_mat1 = zeros(size(resistor_values, 2), size(resistor_values, 2));
% First index has lower resistor on arm
% Second index has upper resistor on arm
for i = 1:size(resistor_values, 2)
    for j = 1:size(resistor_values, 2)
        resistor_div_mat1(i, j) = V_supply * resistor_values(i) / (resistor_values(i) + resistor_values(j));
    end
end
dev_m = (min_V - resistor_div_mat1);  % Voltage deviations, resistor_div_mat must be just lesser than min_V for OpAmp stage
dev_m(dev_m < 0) = NaN;
min_value1 = min(dev_m(:));
[x, y] = find(dev_m == min_value1);
fprintf(" ---- Voltage divider side arm definition & new voltages ---- \n");
fprintf("Upper resistor is %f kΩ, lower resistor is %f kΩ\n", resistor_values(y), resistor_values(x));
v_min_sa = resistor_div_mat1(x, y);    % Voltage reference for side arm
fprintf("Voltage obtained here: %f V -> 'From resistor_div_mat1(%d, %d)'\n", v_min_sa, x, y);
% New voltage deviations
min_dV1 = min_V1 - v_min_sa;
max_dV1 = max_V1 - v_min_sa;
delta_V1 = max_dV1 - min_dV1;
min_dV2 = min_V2 - v_min_sa;
max_dV2 = max_V2 - v_min_sa;
delta_V2 = max_dV2 - min_dV2;
fprintf("Deviation on 2.2 inch flex sensor: %f V to %f V [%f V] (actual)\n", min_dV1, max_dV1, delta_V1);
fprintf("Deviation on 4.5 inch flex sensor: %f V to %f V [%f V] (actual)\n", min_dV2, max_dV2, delta_V2);
%% OpAmp analysis
fprintf("\n==== OpAmp analysis ====\n");
% Maximum deviation voltage scaled up to 4.95 V, then everything is scaled
[max_V, max_Vi] = max([max_dV1, max_dV2]);
fprintf("Maximum deviation voltage is %f V, scaling upto 4.95 V\n", max_V);
scaling_factor = 4.95 / max_V;
fprintf("Scaling factor is %f (ideal)\n", scaling_factor);
% Scaling factor * differential voltage values
min_dV_f1 = min_dV1 * scaling_factor;
max_dV_f1 = max_dV1 * scaling_factor;
out_range_f1 = max_dV_f1 - min_dV_f1;  % Deviation for Flex sensor (1)
min_dV_f2 = min_dV2 * scaling_factor;
max_dV_f2 = max_dV2 * scaling_factor;
out_range_f2 = max_dV_f2 - min_dV_f2;  % Deviation for Flex sensor (2)
fprintf("Deviation on 2.2 inch flex sensor: %f V to %f V (ideal final output)\n", min_dV_f1, max_dV_f1);
fprintf("Deviation of 2.2 inch flex Sensor: %f V (ideal) \n", out_range_f1);
fprintf("Deviation on 4.5 inch flex sensor: %f V to %f V (ideal final output)\n", min_dV_f2, max_dV_f2);
fprintf("Deviation of 4.5 inch flex Sendor: %f V (ideal) \n", out_range_f2);
% Final resistance analysis
fprintf(" ---- Final output voltages ---- \n");
% Row has numerator or forward (feedback - Rf) and column has denominator (Ri)
resistor_div_mat2 = zeros(size(resistor_values, 2), size(resistor_values, 2));
for i = 1:size(resistor_values, 2)
    for j = 1:size(resistor_values, 2)
        resistor_div_mat2(i, j) = resistor_values(i)/resistor_values(j);
    end
end
% Resistor values (ratios) must be just a little less than scaling factor
dev_vals = (scaling_factor - resistor_div_mat2);
dev_vals(dev_vals < 0) = NaN;
min_value2 = min(dev_vals(:));
[x, y] = find(dev_vals == min_value2, 1, 'last');  % Get greater resistance values
fprintf("Forward resistor: %f kΩ\n", resistor_values(x));
fprintf("Backward resistor: %f kΩ\n", resistor_values(y));
ascaling_factor = resistor_div_mat2(x, y);
fprintf("This will give the scaling factor: %f (actual) -> From 'resistor_div_mat2(%d, %d)'\n", ascaling_factor, x, y);
% Actual scaling factor * differential voltage values
min_dV_f1 = min_dV1 * ascaling_factor;
max_dV_f1 = max_dV1 * ascaling_factor;
out_range_f1 = max_dV_f1 - min_dV_f1;  % Deviation for Flex sensor (1)
min_dV_f2 = min_dV2 * ascaling_factor;
max_dV_f2 = max_dV2 * ascaling_factor;
out_range_f2 = max_dV_f2 - min_dV_f2;  % Deviation for Flex sensor (2)
fprintf("Deviation on 2.2 inch flex sensor: %f V to %f V (actual final output)\n", min_dV_f1, max_dV_f1);
fprintf("Deviation of 2.2 inch flex Sensor: %f V (actual) \n", out_range_f1);
fprintf("Deviation on 4.5 inch flex sensor: %f V to %f V (actual final output)\n", min_dV_f2, max_dV_f2);
fprintf("Deviation of 4.5 inch flex Sendor: %f V (actual) \n", out_range_f2);
