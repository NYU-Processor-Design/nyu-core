(Note: This document is currently incomplete)
# **I/O:**

## **Inputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```clk```|1-bit|Clock Signal|
|```rstn```|1-bit|Reset Signal|
|```branch_occr```|2-bits|Specifies if instruction is guaranteed to branch, guaranteed to not branch, or could do either|

## **Outputs:**

|Name|Bits wide|Description|
|:---|:---|:---:|
|```branch_taken```|1-bit|Branch Taken Signal|


# **Functionality:**

## **Registers:**
- 1-bit ```curr_pred```
- 2-bit ```incorrect_pred```

## **Combinational Logic Signals**
- 1-bit ```branch_taken```

## **Branch Prediction**

### **Branch Prediction Logic**
- Branch Prediction will be 2-bit, where the predicted branch outcome only changes after two incorrect predictions.
- We will keep track of the number of incorrect predictions in a row in ```incorrect_pred```, and if it reaches 2 we change ```curr_pred``` to the opposite
- - We only bother to predict, and thus possibly increase the counter, for noncertain instructions. Instructions that are guaranteed to branch or not branch just get that value directly output

