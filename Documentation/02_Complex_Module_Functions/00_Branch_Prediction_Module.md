# **I/O:**

## **Inputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```clk```|1-bit|Clock Signal|
|```rstn_h```|1-bit|Hard Reset Signal|
|```act_taken```|1-bit|Actual branch taken|
|```pred_taken```|1-bit|Predicted branch taken|
|```branch_cond```|2-bits|Specifies if instruction in MEM is guaranteed to branch or we predicted|
|```branch_occr```|2-bits|Specifies if instruction in ID is guaranteed to branch, guaranteed to not branch, or could do either|

## **Outputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```branch_taken```|1-bit|Branch Taken Signal|

# **Functionality:**

## **Registers:**
- 1-bit ```curr_pred```
- 1-bit ```incorrect_pred```

## **Combinational Logic Signals**
- 1-bit ```branch_taken```

## **Branch Prediction**

### **Branch Prediction Description**
- Branch Prediction will be 2-bit, where the predicted branch outcome only changes after two incorrect predictions
- We will keep track if we predicted incorrectly for the last branch prediction in ```incorrect_pred```, and if we incorrectly predict while it is already 1 we change ```curr_pred``` to the opposite. A correct prediction resets ```incorrect_pred``` to 0.
- We only bother to predict, and thus possibly increase the counter, for noncertain instructions. Instructions that are guaranteed to branch or not branch just get that value directly output
- The act_taken signal tells us if our prediction was correct or not and is received in the MEM phase

### **Branch Prediction Logic**

#### **Combinational**
 - ```branch_occr```
    |```branch_occr```|```reg```|
    |---|---|
    |```branch_occr[1] == 0```|```branch_taken = branch_occr[0]```|
    |```branch_occr[1] == 1```|```branch_taken = curr_pred```|

#### **Sequential**
 - if ```^branch_cond == 0```, ```curr_pred``` and ```incorrect_pred``` stay the same
 - else if ```act_taken``` ^ ```pred_taken``` == 0, ```incorrect_pred``` = 0 and ```curr_pred``` stays the same
 - else if ```act_taken``` ^ ```pred_taken``` == 1 and ```incorrect_pred``` == 1, ```curr_pred``` = ~```curr_pred```
 - else ```incorrect_pred``` == 1 and ```curr_pred``` stays the same

## **Reseting**
- Note that because this module needs to keep track of incorrect predictions even after a soft reset to flush the pipeline, it cannot be connected to the rstn line, instead we use rstn_h which is a hard reset line that pull rstn low when it is pulled low but is not necessarily pulled low when rstn is. The rstn_h line is what will be used to hardware reset the core on boot.

